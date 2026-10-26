#include "UdpPacket.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

Frame::Frame(std::unique_ptr<Message> message) : message_(std::move(message)) {}

Frame::Frame(const Frame& other)
  : mach_packet_header_(other.mach_packet_header_), message_(other.message_ ? other.message_->clone() : nullptr), trailer_(other.trailer_) {}

Frame& Frame::operator=(const Frame& other) {
    if (this != &other) {
        mach_packet_header_ = other.mach_packet_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
        trailer_ = other.trailer_;
    }
    return *this;
}

const MachPacketHeader& Frame::mach_packet_header() const { return mach_packet_header_; }
MachPacketHeader& Frame::mach_packet_header() { return mach_packet_header_; }
void Frame::set_mach_packet_header(const MachPacketHeader& value) { mach_packet_header_ = value; }

const Message* Frame::message() const { return message_.get(); }
Message* Frame::message() { return message_.get(); }
void Frame::set_message(std::unique_ptr<Message> message) { message_ = std::move(message); }
std::unique_ptr<Message> Frame::release() { return std::move(message_); }
const std::vector<std::byte>& Frame::trailer() const { return trailer_; }
std::vector<std::byte>& Frame::trailer() { return trailer_; }

std::size_t Frame::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += mach_packet_header_.decode(data + offset, length - offset);

    return offset;
}

std::size_t Frame::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Frame", encoded_size(), capacity);

    offset += mach_packet_header_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t Frame::encoded_size() const {
    return mach_packet_header_.encoded_size();
}

void Frame::print(std::ostream& out) const {
    out << "Frame{";
    out << "mach_packet_header=";
    mach_packet_header_.print(out);
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool Frame::operator==(const Frame& other) const {
    if (!(mach_packet_header_ == other.mach_packet_header_)) { return false; }
    if (!(trailer_ == other.trailer_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool Frame::operator!=(const Frame& other) const { return !(*this == other); }

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

    kind_ = Kind::Messages;

    while (offset < length) {
        const std::size_t start = offset;
        Frame frame;
        offset += frame.decode(data + offset, length - offset);
        const std::size_t frame_size = wire::count(frame.mach_packet_header().mach_packet_length());
        wire::require("UdpPacket", start + frame_size, length);
        const std::size_t body = start + frame_size - offset;
        std::unique_ptr<Message> message = Factory::create(frame.mach_packet_header().mach_packet_type());
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


    if (kind_ != Kind::Messages) { return offset; }

    for (const Frame& frame : frames_) {
        if (frame.message() == nullptr) { throw EncodeError("UdpPacket", "a frame holds no message"); }
        const std::size_t frame_size = frame.encoded_size() + frame.message()->encoded_size() + frame.trailer().size();

        auto mach_packet_header = frame.mach_packet_header();
        mach_packet_header.set_mach_packet_length(static_cast<std::uint16_t>(frame_size));
        mach_packet_header.set_mach_packet_type(frame.message()->type());

        offset += mach_packet_header.encode(data + offset, capacity - offset);

        offset += frame.message()->encode(data + offset, capacity - offset);
        wire::write_bytes(data + offset, frame.trailer().data(), frame.trailer().size());
        offset += frame.trailer().size();
    }

    wire::write_bytes(data + offset, trailer_.data(), trailer_.size());
    offset += trailer_.size();

    return offset;
}

std::size_t UdpPacket::encoded_size() const {
    std::size_t total = 0;
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
    out << ", frames=";
    print::sequence(out, frames_);
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool UdpPacket::operator==(const UdpPacket& other) const {
    return kind_ == other.kind_ && frames_ == other.frames_ && trailer_ == other.trailer_;
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

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
