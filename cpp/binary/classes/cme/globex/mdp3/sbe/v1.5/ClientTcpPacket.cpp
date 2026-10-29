#include "ClientTcpPacket.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

ClientTcpFrame::ClientTcpFrame(std::unique_ptr<ClientTcpMessage> message) : message_(std::move(message)) {}

ClientTcpFrame::ClientTcpFrame(const ClientTcpFrame& other)
  : client_technical_header_(other.client_technical_header_), message_header_(other.message_header_), message_(other.message_ ? other.message_->clone() : nullptr), trailer_(other.trailer_) {}

ClientTcpFrame& ClientTcpFrame::operator=(const ClientTcpFrame& other) {
    if (this != &other) {
        client_technical_header_ = other.client_technical_header_;
        message_header_ = other.message_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
        trailer_ = other.trailer_;
    }
    return *this;
}

const ClientTechnicalHeader& ClientTcpFrame::client_technical_header() const { return client_technical_header_; }
ClientTechnicalHeader& ClientTcpFrame::client_technical_header() { return client_technical_header_; }
void ClientTcpFrame::set_client_technical_header(const ClientTechnicalHeader& value) { client_technical_header_ = value; }

const MessageHeader& ClientTcpFrame::message_header() const { return message_header_; }
MessageHeader& ClientTcpFrame::message_header() { return message_header_; }
void ClientTcpFrame::set_message_header(const MessageHeader& value) { message_header_ = value; }

const ClientTcpMessage* ClientTcpFrame::message() const { return message_.get(); }
ClientTcpMessage* ClientTcpFrame::message() { return message_.get(); }
void ClientTcpFrame::set_message(std::unique_ptr<ClientTcpMessage> message) { message_ = std::move(message); }
std::unique_ptr<ClientTcpMessage> ClientTcpFrame::release() { return std::move(message_); }
const std::vector<std::byte>& ClientTcpFrame::trailer() const { return trailer_; }
std::vector<std::byte>& ClientTcpFrame::trailer() { return trailer_; }

std::size_t ClientTcpFrame::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += client_technical_header_.decode(data + offset, length - offset);

    offset += message_header_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ClientTcpFrame::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClientTcpFrame", encoded_size(), capacity);

    offset += client_technical_header_.encode(data + offset, capacity - offset);

    offset += message_header_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ClientTcpFrame::encoded_size() const {
    return client_technical_header_.encoded_size() + message_header_.encoded_size();
}

void ClientTcpFrame::print(std::ostream& out) const {
    out << "ClientTcpFrame{";
    out << "client_technical_header=";
    client_technical_header_.print(out);
    out << ", ";
    out << "message_header=";
    message_header_.print(out);
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool ClientTcpFrame::operator==(const ClientTcpFrame& other) const {
    if (!(client_technical_header_ == other.client_technical_header_)) { return false; }
    if (!(message_header_ == other.message_header_)) { return false; }
    if (!(trailer_ == other.trailer_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool ClientTcpFrame::operator!=(const ClientTcpFrame& other) const { return !(*this == other); }

const std::vector<ClientTcpFrame>& ClientTcpPacket::frames() const { return frames_; }
std::vector<ClientTcpFrame>& ClientTcpPacket::frames() { return frames_; }
void ClientTcpPacket::add(std::unique_ptr<ClientTcpMessage> message) { frames_.emplace_back(std::move(message)); }

std::size_t ClientTcpPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    frames_.clear();

    while (offset < length) {
        const std::size_t start = offset;

        // A frame the run does not hold in full is the caller's tail, not a fault: stop
        // short of it and leave it out of what this read consumed.
        if (length - start < 24) { break; }

        ClientTcpFrame frame;
        offset += frame.decode(data + offset, length - offset);
        const std::size_t frame_size = wire::count(frame.message_header().message_size()) + 14;
        if (frame_size < 24) { throw DecodeError("ClientTcpPacket", 24, frame_size); }
        if (start + frame_size > length) { offset = start; break; }
        const std::size_t body = start + frame_size - offset;
        std::unique_ptr<ClientTcpMessage> message = ClientTcpMessageFactory::create(frame.message_header().simple_binary_header().template_id());
        // What the message left of its frame: bytes the model does not describe, kept as they came
        const std::size_t used = message->decode(data + offset, body);
        frame.trailer().assign(data + offset + used, data + start + frame_size);
        offset = start + frame_size;
        frame.set_message(std::move(message));
        frames_.push_back(std::move(frame));
    }

    return offset;
}

std::size_t ClientTcpPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClientTcpPacket", encoded_size(), capacity);


    for (const ClientTcpFrame& frame : frames_) {
        if (frame.message() == nullptr) { throw EncodeError("ClientTcpPacket", "a frame holds no message"); }
        const std::size_t frame_size = frame.encoded_size() + frame.message()->encoded_size() + frame.trailer().size();

        auto client_technical_header = frame.client_technical_header();
        auto message_header = frame.message_header();
        message_header.set_message_size(static_cast<std::uint16_t>(frame_size - 14));
        message_header.simple_binary_header().set_template_id(frame.message()->type());

        offset += client_technical_header.encode(data + offset, capacity - offset);

        offset += message_header.encode(data + offset, capacity - offset);

        offset += frame.message()->encode(data + offset, capacity - offset);
        wire::write_bytes(data + offset, frame.trailer().data(), frame.trailer().size());
        offset += frame.trailer().size();
    }

    return offset;
}

std::size_t ClientTcpPacket::encoded_size() const {
    std::size_t total = 0;
    for (const ClientTcpFrame& frame : frames_) {
        total += frame.encoded_size() + (frame.message() ? frame.message()->encoded_size() : 0) + frame.trailer().size();
    }
    return total;
}

void ClientTcpPacket::accept(ClientTcpMessageVisitor& visitor) const {
    for (const ClientTcpFrame& frame : frames_) {
        if (frame.message()) { frame.message()->accept(visitor); }
    }
}

void ClientTcpPacket::print(std::ostream& out) const {
    out << "ClientTcpPacket{";
    out << "frames=";
    print::sequence(out, frames_);
    out << '}';
}

bool ClientTcpPacket::operator==(const ClientTcpPacket& other) const {
    return frames_ == other.frames_;
}

bool ClientTcpPacket::operator!=(const ClientTcpPacket& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& out, const ClientTcpFrame& frame) { frame.print(out); return out; }
std::ostream& operator<<(std::ostream& out, const ClientTcpPacket& stream) { stream.print(out); return out; }

} // namespace cme::globex::mdp3::sbe::v1_5
