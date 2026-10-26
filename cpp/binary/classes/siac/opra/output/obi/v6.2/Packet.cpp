#include "Packet.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace siac::opra::output::obi::v6_2 {

Frame::Frame(std::unique_ptr<Message> message) : message_(std::move(message)) {}

Frame::Frame(const Frame& other)
  : message_header_(other.message_header_), message_(other.message_ ? other.message_->clone() : nullptr) {}

Frame& Frame::operator=(const Frame& other) {
    if (this != &other) {
        message_header_ = other.message_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
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
    out << '}';
}

bool Frame::operator==(const Frame& other) const {
    if (!(message_header_ == other.message_header_)) { return false; }
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
        Frame frame;
        offset += frame.decode(data + offset, length - offset);
        const std::size_t body = length - offset;
        std::unique_ptr<Message> message = Factory::create(frame.message_header().message_category());
        offset += message->decode(data + offset, body);
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

        auto message_header = frame.message_header();
        message_header.set_message_category(frame.message()->type());

        offset += message_header.encode(data + offset, capacity - offset);

        offset += frame.message()->encode(data + offset, capacity - offset);
    }

    wire::write_bytes(data + offset, trailer_.data(), trailer_.size());
    offset += trailer_.size();

    return offset;
}

std::size_t Packet::encoded_size() const {
    std::size_t total = block_header_.encoded_size();
    if (kind_ == Kind::Messages) {
        for (const Frame& frame : frames_) {
            total += frame.encoded_size() + (frame.message() ? frame.message()->encoded_size() : 0);
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

} // namespace siac::opra::output::obi::v6_2
