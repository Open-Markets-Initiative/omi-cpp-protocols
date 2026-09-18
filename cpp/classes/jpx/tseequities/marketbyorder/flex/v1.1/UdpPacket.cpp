#include "UdpPacket.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

Frame::Frame(std::unique_ptr<Message> message) : message_(std::move(message)) {}

Frame::Frame(const Frame& other)
  : message_header_(other.message_header_), message_(other.message_ ? other.message_->clone() : nullptr), trailer_(other.trailer_) {}

Frame& Frame::operator=(const Frame& other) {
    if (this != &other) {
        message_header_ = other.message_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
        trailer_ = other.trailer_;
    }
    return *this;
}

const MessageHeader& Frame::message_header() const { return message_header_; }
MessageHeader& Frame::message_header() { return message_header_; }
void Frame::set_message_header(const MessageHeader& value) { message_header_ = value; }

const Message* Frame::message() const { return message_.get(); }
Message* Frame::message() { return message_.get(); }
void Frame::set_message(std::unique_ptr<Message> message) { message_ = std::move(message); }
std::unique_ptr<Message> Frame::release() { return std::move(message_); }
const std::vector<std::byte>& Frame::trailer() const { return trailer_; }
std::vector<std::byte>& Frame::trailer() { return trailer_; }

std::size_t Frame::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += message_header_.decode(data + offset, length - offset);

    return offset;
}

std::size_t Frame::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Frame", encoded_size(), capacity);

    offset += message_header_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t Frame::encoded_size() const {
    return message_header_.encoded_size();
}

void Frame::print(std::ostream& out) const {
    out << "Frame{";
    out << "message_header=";
    message_header_.print(out);
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool Frame::operator==(const Frame& other) const {
    if (!(message_header_ == other.message_header_)) { return false; }
    if (!(trailer_ == other.trailer_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool Frame::operator!=(const Frame& other) const { return !(*this == other); }

const PacketHeader& UdpPacket::packet_header() const { return packet_header_; }
PacketHeader& UdpPacket::packet_header() { return packet_header_; }
void UdpPacket::set_packet_header(const PacketHeader& value) { packet_header_ = value; }

UdpPacket::Kind UdpPacket::kind() const { return kind_; }
void UdpPacket::set_kind(Kind value) { kind_ = value; }

const std::vector<Frame>& UdpPacket::frames() const { return frames_; }
std::vector<Frame>& UdpPacket::frames() { return frames_; }
const std::vector<std::byte>& UdpPacket::trailer() const { return trailer_; }
std::vector<std::byte>& UdpPacket::trailer() { return trailer_; }
void UdpPacket::add(std::unique_ptr<Message> message) { frames_.emplace_back(std::move(message)); }

std::size_t UdpPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    frames_.clear();
    trailer_.clear();

    offset += packet_header_.decode(data + offset, length - offset);

    kind_ = Kind::Messages;

    const std::size_t count = static_cast<std::size_t>(packet_header_.message_count());

    for (std::size_t index = 0; index < count; ++index) {
        const std::size_t start = offset;
        Frame frame;
        offset += frame.decode(data + offset, length - offset);
        const std::size_t frame_size = static_cast<std::size_t>(frame.message_header().tag_length()) + 1;
        wire::require("UdpPacket", start + frame_size, length);
        const std::size_t body = start + frame_size - offset;
        std::unique_ptr<Message> message = Factory::create(frame.message_header().message_type());
        // What the message left of its frame: bytes the model does not describe, kept as they came
        const std::size_t used = message->decode(data + offset, body);
        frame.trailer().assign(data + offset + used, data + start + frame_size);
        offset = start + frame_size;
        frame.set_message(std::move(message));
        frames_.push_back(std::move(frame));
    }

    // What the frames left behind: a pad or trailer the model does not describe, kept
    // as it came so the packet still encodes back to the bytes it was read from.
    trailer_.assign(data + offset, data + length);
    offset = length;

    return offset;
}

std::size_t UdpPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPacket", encoded_size(), capacity);

    auto packet_header = packet_header_;
    if (kind_ == Kind::Messages) { packet_header.set_message_count(static_cast<std::uint8_t>(frames_.size())); }

    offset += packet_header.encode(data + offset, capacity - offset);

    if (kind_ != Kind::Messages) { return offset; }

    for (const Frame& frame : frames_) {
        if (frame.message() == nullptr) { throw EncodeError("UdpPacket", "a frame holds no message"); }
        const std::size_t frame_size = frame.encoded_size() + frame.message()->encoded_size() + frame.trailer().size();

        auto message_header = frame.message_header();
        message_header.set_tag_length(static_cast<std::uint8_t>(frame_size - 1));
        message_header.set_message_type(frame.message()->type());

        offset += message_header.encode(data + offset, capacity - offset);

        offset += frame.message()->encode(data + offset, capacity - offset);
        wire::write_bytes(data + offset, frame.trailer().data(), frame.trailer().size());
        offset += frame.trailer().size();
    }

    wire::write_bytes(data + offset, trailer_.data(), trailer_.size());
    offset += trailer_.size();

    return offset;
}

std::size_t UdpPacket::encoded_size() const {
    std::size_t total = packet_header_.encoded_size();
    if (kind_ == Kind::Messages) {
        for (const Frame& frame : frames_) {
            total += frame.encoded_size() + (frame.message() ? frame.message()->encoded_size() : 0) + frame.trailer().size();
        }
        total += trailer_.size();
    }
    return total;
}

void UdpPacket::accept(Visitor& visitor) const {
    for (const Frame& frame : frames_) {
        if (frame.message()) { frame.message()->accept(visitor); }
    }
}

void UdpPacket::print(std::ostream& out) const {
    out << "UdpPacket{kind=" << kind_;
    out << ", packet_header=";
    packet_header_.print(out);
    out << ", frames=";
    print::sequence(out, frames_);
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool UdpPacket::operator==(const UdpPacket& other) const {
    return kind_ == other.kind_ && packet_header_ == other.packet_header_ && frames_ == other.frames_ && trailer_ == other.trailer_;
}

bool UdpPacket::operator!=(const UdpPacket& other) const { return !(*this == other); }

std::string_view to_string(UdpPacket::Kind kind) {
    switch (kind) {
        case UdpPacket::Kind::Messages: return "Messages";
        default: return "?";
    }
}

std::ostream& operator<<(std::ostream& out, UdpPacket::Kind kind) { return out << to_string(kind); }
std::ostream& operator<<(std::ostream& out, const Frame& frame) { frame.print(out); return out; }
std::ostream& operator<<(std::ostream& out, const UdpPacket& packet) { packet.print(out); return out; }

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
