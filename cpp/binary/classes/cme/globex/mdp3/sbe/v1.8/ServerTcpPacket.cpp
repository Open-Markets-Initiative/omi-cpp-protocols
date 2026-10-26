#include "ServerTcpPacket.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

ServerTcpFrame::ServerTcpFrame(std::unique_ptr<ServerTcpMessage> message) : message_(std::move(message)) {}

ServerTcpFrame::ServerTcpFrame(const ServerTcpFrame& other)
  : server_technical_header_(other.server_technical_header_), message_header_(other.message_header_), message_(other.message_ ? other.message_->clone() : nullptr), trailer_(other.trailer_) {}

ServerTcpFrame& ServerTcpFrame::operator=(const ServerTcpFrame& other) {
    if (this != &other) {
        server_technical_header_ = other.server_technical_header_;
        message_header_ = other.message_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
        trailer_ = other.trailer_;
    }
    return *this;
}

const ServerTechnicalHeader& ServerTcpFrame::server_technical_header() const { return server_technical_header_; }
ServerTechnicalHeader& ServerTcpFrame::server_technical_header() { return server_technical_header_; }
void ServerTcpFrame::set_server_technical_header(const ServerTechnicalHeader& value) { server_technical_header_ = value; }

const MessageHeader& ServerTcpFrame::message_header() const { return message_header_; }
MessageHeader& ServerTcpFrame::message_header() { return message_header_; }
void ServerTcpFrame::set_message_header(const MessageHeader& value) { message_header_ = value; }

const ServerTcpMessage* ServerTcpFrame::message() const { return message_.get(); }
ServerTcpMessage* ServerTcpFrame::message() { return message_.get(); }
void ServerTcpFrame::set_message(std::unique_ptr<ServerTcpMessage> message) { message_ = std::move(message); }
std::unique_ptr<ServerTcpMessage> ServerTcpFrame::release() { return std::move(message_); }
const std::vector<std::byte>& ServerTcpFrame::trailer() const { return trailer_; }
std::vector<std::byte>& ServerTcpFrame::trailer() { return trailer_; }

std::size_t ServerTcpFrame::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += server_technical_header_.decode(data + offset, length - offset);

    offset += message_header_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ServerTcpFrame::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerTcpFrame", encoded_size(), capacity);

    offset += server_technical_header_.encode(data + offset, capacity - offset);

    offset += message_header_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ServerTcpFrame::encoded_size() const {
    return server_technical_header_.encoded_size() + message_header_.encoded_size();
}

void ServerTcpFrame::print(std::ostream& out) const {
    out << "ServerTcpFrame{";
    out << "server_technical_header=";
    server_technical_header_.print(out);
    out << ", ";
    out << "message_header=";
    message_header_.print(out);
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool ServerTcpFrame::operator==(const ServerTcpFrame& other) const {
    if (!(server_technical_header_ == other.server_technical_header_)) { return false; }
    if (!(message_header_ == other.message_header_)) { return false; }
    if (!(trailer_ == other.trailer_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool ServerTcpFrame::operator!=(const ServerTcpFrame& other) const { return !(*this == other); }

const std::vector<ServerTcpFrame>& ServerTcpPacket::frames() const { return frames_; }
std::vector<ServerTcpFrame>& ServerTcpPacket::frames() { return frames_; }
void ServerTcpPacket::add(std::unique_ptr<ServerTcpMessage> message) { frames_.emplace_back(std::move(message)); }

std::size_t ServerTcpPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    frames_.clear();

    while (offset < length) {
        const std::size_t start = offset;

        // A frame the run does not hold in full is the caller's tail, not a fault: stop
        // short of it and leave it out of what this read consumed.
        if (length - start < 24) { break; }

        ServerTcpFrame frame;
        offset += frame.decode(data + offset, length - offset);
        const std::size_t frame_size = wire::count(frame.message_header().message_size()) + 14;
        if (frame_size < 24) { throw DecodeError("ServerTcpPacket", 24, frame_size); }
        if (start + frame_size > length) { offset = start; break; }
        const std::size_t body = start + frame_size - offset;
        std::unique_ptr<ServerTcpMessage> message = ServerTcpMessageFactory::create(frame.message_header().simple_binary_header().template_id());
        // What the message left of its frame: bytes the model does not describe, kept as they came
        const std::size_t used = message->decode(data + offset, body);
        frame.trailer().assign(data + offset + used, data + start + frame_size);
        offset = start + frame_size;
        frame.set_message(std::move(message));
        frames_.push_back(std::move(frame));
    }

    return offset;
}

std::size_t ServerTcpPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerTcpPacket", encoded_size(), capacity);


    for (const ServerTcpFrame& frame : frames_) {
        if (frame.message() == nullptr) { throw EncodeError("ServerTcpPacket", "a frame holds no message"); }
        const std::size_t frame_size = frame.encoded_size() + frame.message()->encoded_size() + frame.trailer().size();

        auto server_technical_header = frame.server_technical_header();
        auto message_header = frame.message_header();
        message_header.set_message_size(static_cast<std::uint16_t>(frame_size - 14));
        message_header.simple_binary_header().set_template_id(frame.message()->type());

        offset += server_technical_header.encode(data + offset, capacity - offset);

        offset += message_header.encode(data + offset, capacity - offset);

        offset += frame.message()->encode(data + offset, capacity - offset);
        wire::write_bytes(data + offset, frame.trailer().data(), frame.trailer().size());
        offset += frame.trailer().size();
    }

    return offset;
}

std::size_t ServerTcpPacket::encoded_size() const {
    std::size_t total = 0;
    for (const ServerTcpFrame& frame : frames_) {
        total += frame.encoded_size() + (frame.message() ? frame.message()->encoded_size() : 0) + frame.trailer().size();
    }
    return total;
}

void ServerTcpPacket::accept(ServerTcpMessageVisitor& visitor) const {
    for (const ServerTcpFrame& frame : frames_) {
        if (frame.message()) { frame.message()->accept(visitor); }
    }
}

void ServerTcpPacket::print(std::ostream& out) const {
    out << "ServerTcpPacket{";
    out << "frames=";
    print::sequence(out, frames_);
    out << '}';
}

bool ServerTcpPacket::operator==(const ServerTcpPacket& other) const {
    return frames_ == other.frames_;
}

bool ServerTcpPacket::operator!=(const ServerTcpPacket& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& out, const ServerTcpFrame& frame) { frame.print(out); return out; }
std::ostream& operator<<(std::ostream& out, const ServerTcpPacket& stream) { stream.print(out); return out; }

} // namespace cme::globex::mdp3::sbe::v1_8
