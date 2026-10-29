#include "Packet.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace siac::cts::output::cta::v1_91 {

Frame::Frame(std::unique_ptr<Message> message) : message_(std::move(message)) {}

Frame::Frame(const Frame& other)
  : message_length_(other.message_length_), message_category_(other.message_category_), message_(other.message_ ? other.message_->clone() : nullptr), trailer_(other.trailer_) {}

Frame& Frame::operator=(const Frame& other) {
    if (this != &other) {
        message_length_ = other.message_length_;
        message_category_ = other.message_category_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
        trailer_ = other.trailer_;
    }
    return *this;
}

std::uint16_t Frame::message_length() const { return message_length_; }
void Frame::set_message_length(std::uint16_t value) { message_length_ = value; }

MessageCategory Frame::message_category() const { return message_category_; }
void Frame::set_message_category(MessageCategory value) { message_category_ = value; }

const Message* Frame::message() const { return message_.get(); }
Message* Frame::message() { return message_.get(); }
void Frame::set_message(std::unique_ptr<Message> message) { message_ = std::move(message); }
std::unique_ptr<Message> Frame::release() { return std::move(message_); }
const std::vector<std::byte>& Frame::trailer() const { return trailer_; }
std::vector<std::byte>& Frame::trailer() { return trailer_; }

std::size_t Frame::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("Frame", offset + 2, length);
    message_length_ = wire::read_u16_be(data + offset);
    offset += 2;

    wire::require("Frame", offset + 1, length);
    message_category_ = static_cast<MessageCategory>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t Frame::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Frame", encoded_size(), capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(message_length_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(message_category_));
    offset += 1;

    return offset;
}

std::size_t Frame::encoded_size() const {
    return 2 + 1;
}

void Frame::print(std::ostream& out) const {
    out << "Frame{";
    out << "message_length=";
    out << message_length_;
    out << ", ";
    out << "message_category=";
    out << message_category_;
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool Frame::operator==(const Frame& other) const {
    if (!(message_length_ == other.message_length_)) { return false; }
    if (!(message_category_ == other.message_category_)) { return false; }
    if (!(trailer_ == other.trailer_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool Frame::operator!=(const Frame& other) const { return !(*this == other); }

const BlockHeader& Packet::block_header() const { return block_header_; }
BlockHeader& Packet::block_header() { return block_header_; }
void Packet::set_block_header(const BlockHeader& value) { block_header_ = value; }

Packet::Kind Packet::kind() const { return kind_; }
void Packet::set_kind(Kind value) { kind_ = value; }

const std::vector<Frame>& Packet::frames() const { return frames_; }
std::vector<Frame>& Packet::frames() { return frames_; }
const std::vector<std::byte>& Packet::trailer() const { return trailer_; }
std::vector<std::byte>& Packet::trailer() { return trailer_; }
void Packet::add(std::unique_ptr<Message> message) { frames_.emplace_back(std::move(message)); }

std::size_t Packet::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    frames_.clear();
    trailer_.clear();

    offset += block_header_.decode(data + offset, length - offset);

    kind_ = Kind::Messages;

    const std::size_t count = wire::count(block_header_.messages_in_block());

    for (std::size_t index = 0; index < count; ++index) {
        const std::size_t start = offset;
        Frame frame;
        offset += frame.decode(data + offset, length - offset);
        const std::size_t frame_size = wire::count(frame.message_length());
        wire::require("Packet", start + frame_size, length);
        const std::size_t body = start + frame_size - offset;
        std::unique_ptr<Message> message = Factory::create(frame.message_category());
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

std::size_t Packet::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Packet", encoded_size(), capacity);

    auto block_header = block_header_;
    if (kind_ == Kind::Messages) { block_header.set_messages_in_block(static_cast<std::uint8_t>(frames_.size())); }

    offset += block_header.encode(data + offset, capacity - offset);

    if (kind_ != Kind::Messages) { return offset; }

    for (const Frame& frame : frames_) {
        if (frame.message() == nullptr) { throw EncodeError("Packet", "a frame holds no message"); }
        const std::size_t frame_size = frame.encoded_size() + frame.message()->encoded_size() + frame.trailer().size();

        auto message_length = frame.message_length();
        auto message_category = frame.message_category();
        message_length = static_cast<std::uint16_t>(frame_size);
        message_category = frame.message()->type();

        wire::write_u16_be(data + offset, static_cast<std::uint16_t>(message_length));
        offset += 2;

        wire::write_char(data + offset, static_cast<char>(message_category));
        offset += 1;

        offset += frame.message()->encode(data + offset, capacity - offset);
        wire::write_bytes(data + offset, frame.trailer().data(), frame.trailer().size());
        offset += frame.trailer().size();
    }

    wire::write_bytes(data + offset, trailer_.data(), trailer_.size());
    offset += trailer_.size();

    return offset;
}

std::size_t Packet::encoded_size() const {
    std::size_t total = block_header_.encoded_size();
    if (kind_ == Kind::Messages) {
        for (const Frame& frame : frames_) {
            total += frame.encoded_size() + (frame.message() ? frame.message()->encoded_size() : 0) + frame.trailer().size();
        }
        total += trailer_.size();
    }
    return total;
}

void Packet::accept(Visitor& visitor) const {
    for (const Frame& frame : frames_) {
        if (frame.message()) { frame.message()->accept(visitor); }
    }
}

void Packet::print(std::ostream& out) const {
    out << "Packet{kind=" << kind_;
    out << ", block_header=";
    block_header_.print(out);
    out << ", frames=";
    print::sequence(out, frames_);
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool Packet::operator==(const Packet& other) const {
    return kind_ == other.kind_ && block_header_ == other.block_header_ && frames_ == other.frames_ && trailer_ == other.trailer_;
}

bool Packet::operator!=(const Packet& other) const { return !(*this == other); }

std::string_view to_string(Packet::Kind kind) {
    switch (kind) {
        case Packet::Kind::Messages: return "Messages";
        default: return "?";
    }
}

std::ostream& operator<<(std::ostream& out, Packet::Kind kind) { return out << to_string(kind); }
std::ostream& operator<<(std::ostream& out, const Frame& frame) { frame.print(out); return out; }
std::ostream& operator<<(std::ostream& out, const Packet& packet) { packet.print(out); return out; }

} // namespace siac::cts::output::cta::v1_91
