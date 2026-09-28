#include "ClientPacket.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

Frame::Frame(std::unique_ptr<Message> message) : message_(std::move(message)) {}

Frame::Frame(const Frame& other)
  : client_packet_header_(other.client_packet_header_), message_(other.message_ ? other.message_->clone() : nullptr), trailer_(other.trailer_) {}

Frame& Frame::operator=(const Frame& other) {
    if (this != &other) {
        client_packet_header_ = other.client_packet_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
        trailer_ = other.trailer_;
    }
    return *this;
}

const ClientPacketHeader& Frame::client_packet_header() const { return client_packet_header_; }
ClientPacketHeader& Frame::client_packet_header() { return client_packet_header_; }
void Frame::set_client_packet_header(const ClientPacketHeader& value) { client_packet_header_ = value; }

const Message* Frame::message() const { return message_.get(); }
Message* Frame::message() { return message_.get(); }
void Frame::set_message(std::unique_ptr<Message> message) { message_ = std::move(message); }
std::unique_ptr<Message> Frame::release() { return std::move(message_); }
const std::vector<std::byte>& Frame::trailer() const { return trailer_; }
std::vector<std::byte>& Frame::trailer() { return trailer_; }

std::size_t Frame::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += client_packet_header_.decode(data + offset, length - offset);

    return offset;
}

std::size_t Frame::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Frame", encoded_size(), capacity);

    offset += client_packet_header_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t Frame::encoded_size() const {
    return client_packet_header_.encoded_size();
}

void Frame::print(std::ostream& out) const {
    out << "Frame{";
    out << "client_packet_header=";
    client_packet_header_.print(out);
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool Frame::operator==(const Frame& other) const {
    if (!(client_packet_header_ == other.client_packet_header_)) { return false; }
    if (!(trailer_ == other.trailer_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool Frame::operator!=(const Frame& other) const { return !(*this == other); }

const std::vector<Frame>& ClientPacket::frames() const { return frames_; }
std::vector<Frame>& ClientPacket::frames() { return frames_; }
void ClientPacket::add(std::unique_ptr<Message> message) { frames_.emplace_back(std::move(message)); }

std::size_t ClientPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    frames_.clear();

    while (offset < length) {
        const std::size_t start = offset;

        // A frame the run does not hold in full is the caller's tail, not a fault: stop
        // short of it and leave it out of what this read consumed.
        if (length - start < 3) { break; }

        Frame frame;
        offset += frame.decode(data + offset, length - offset);
        const std::size_t frame_size = static_cast<std::size_t>(frame.client_packet_header().packet_length()) + 2;
        if (frame_size < 3) { throw DecodeError("ClientPacket", 3, frame_size); }
        if (start + frame_size > length) { offset = start; break; }
        const std::size_t body = start + frame_size - offset;
        std::unique_ptr<Message> message = Factory::create(frame.client_packet_header().client_packet_type());
        // What the message left of its frame: bytes the model does not describe, kept as they came
        const std::size_t used = message->decode(data + offset, body);
        frame.trailer().assign(data + offset + used, data + start + frame_size);
        offset = start + frame_size;
        frame.set_message(std::move(message));
        frames_.push_back(std::move(frame));
    }

    return offset;
}

std::size_t ClientPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClientPacket", encoded_size(), capacity);


    for (const Frame& frame : frames_) {
        if (frame.message() == nullptr) { throw EncodeError("ClientPacket", "a frame holds no message"); }
        const std::size_t frame_size = frame.encoded_size() + frame.message()->encoded_size() + frame.trailer().size();

        auto client_packet_header = frame.client_packet_header();
        client_packet_header.set_packet_length(static_cast<std::uint16_t>(frame_size - 2));
        client_packet_header.set_client_packet_type(frame.message()->type());

        offset += client_packet_header.encode(data + offset, capacity - offset);

        offset += frame.message()->encode(data + offset, capacity - offset);
        wire::write_bytes(data + offset, frame.trailer().data(), frame.trailer().size());
        offset += frame.trailer().size();
    }

    return offset;
}

std::size_t ClientPacket::encoded_size() const {
    std::size_t total = 0;
    for (const Frame& frame : frames_) {
        total += frame.encoded_size() + (frame.message() ? frame.message()->encoded_size() : 0) + frame.trailer().size();
    }
    return total;
}

void ClientPacket::accept(Visitor& visitor) const {
    for (const Frame& frame : frames_) {
        if (frame.message()) { frame.message()->accept(visitor); }
    }
}

void ClientPacket::print(std::ostream& out) const {
    out << "ClientPacket{";
    out << "frames=";
    print::sequence(out, frames_);
    out << '}';
}

bool ClientPacket::operator==(const ClientPacket& other) const {
    return frames_ == other.frames_;
}

bool ClientPacket::operator!=(const ClientPacket& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& out, const Frame& frame) { frame.print(out); return out; }
std::ostream& operator<<(std::ostream& out, const ClientPacket& stream) { stream.print(out); return out; }

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
