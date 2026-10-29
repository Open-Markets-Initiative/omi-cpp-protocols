#include "Stream.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

Frame::Frame(std::unique_ptr<Message> message) : message_(std::move(message)) {}

Frame::Frame(const Frame& other)
  : simple_open_framing_header_(other.simple_open_framing_header_), message_header_(other.message_header_), message_(other.message_ ? other.message_->clone() : nullptr), trailer_(other.trailer_) {}

Frame& Frame::operator=(const Frame& other) {
    if (this != &other) {
        simple_open_framing_header_ = other.simple_open_framing_header_;
        message_header_ = other.message_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
        trailer_ = other.trailer_;
    }
    return *this;
}

const SimpleOpenFramingHeader& Frame::simple_open_framing_header() const { return simple_open_framing_header_; }
SimpleOpenFramingHeader& Frame::simple_open_framing_header() { return simple_open_framing_header_; }
void Frame::set_simple_open_framing_header(const SimpleOpenFramingHeader& value) { simple_open_framing_header_ = value; }

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

    offset += simple_open_framing_header_.decode(data + offset, length - offset);

    offset += message_header_.decode(data + offset, length - offset);

    return offset;
}

std::size_t Frame::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Frame", encoded_size(), capacity);

    offset += simple_open_framing_header_.encode(data + offset, capacity - offset);

    offset += message_header_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t Frame::encoded_size() const {
    return simple_open_framing_header_.encoded_size() + message_header_.encoded_size();
}

void Frame::print(std::ostream& out) const {
    out << "Frame{";
    out << "simple_open_framing_header=";
    simple_open_framing_header_.print(out);
    out << ", ";
    out << "message_header=";
    message_header_.print(out);
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool Frame::operator==(const Frame& other) const {
    if (!(simple_open_framing_header_ == other.simple_open_framing_header_)) { return false; }
    if (!(message_header_ == other.message_header_)) { return false; }
    if (!(trailer_ == other.trailer_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool Frame::operator!=(const Frame& other) const { return !(*this == other); }

const std::vector<Frame>& Stream::frames() const { return frames_; }
std::vector<Frame>& Stream::frames() { return frames_; }
void Stream::add(std::unique_ptr<Message> message) { frames_.emplace_back(std::move(message)); }

std::size_t Stream::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    frames_.clear();

    while (offset < length) {
        const std::size_t start = offset;

        // A frame the run does not hold in full is the caller's tail, not a fault: stop
        // short of it and leave it out of what this read consumed.
        if (length - start < 12) { break; }

        Frame frame;
        offset += frame.decode(data + offset, length - offset);
        const std::size_t frame_size = wire::count(frame.simple_open_framing_header().message_length());
        if (frame_size < 12) { throw DecodeError("Stream", 12, frame_size); }
        if (start + frame_size > length) { offset = start; break; }
        const std::size_t body = start + frame_size - offset;
        std::unique_ptr<Message> message = Factory::create(frame.message_header().template_id());
        // What the message left of its frame: bytes the model does not describe, kept as they came
        const std::size_t used = message->decode(data + offset, body);
        frame.trailer().assign(data + offset + used, data + start + frame_size);
        offset = start + frame_size;
        frame.set_message(std::move(message));
        frames_.push_back(std::move(frame));
    }

    return offset;
}

std::size_t Stream::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Stream", encoded_size(), capacity);


    for (const Frame& frame : frames_) {
        if (frame.message() == nullptr) { throw EncodeError("Stream", "a frame holds no message"); }
        const std::size_t frame_size = frame.encoded_size() + frame.message()->encoded_size() + frame.trailer().size();

        auto simple_open_framing_header = frame.simple_open_framing_header();
        auto message_header = frame.message_header();
        simple_open_framing_header.set_message_length(static_cast<std::uint16_t>(frame_size));
        message_header.set_template_id(frame.message()->type());

        offset += simple_open_framing_header.encode(data + offset, capacity - offset);

        offset += message_header.encode(data + offset, capacity - offset);

        offset += frame.message()->encode(data + offset, capacity - offset);
        wire::write_bytes(data + offset, frame.trailer().data(), frame.trailer().size());
        offset += frame.trailer().size();
    }

    return offset;
}

std::size_t Stream::encoded_size() const {
    std::size_t total = 0;
    for (const Frame& frame : frames_) {
        total += frame.encoded_size() + (frame.message() ? frame.message()->encoded_size() : 0) + frame.trailer().size();
    }
    return total;
}

void Stream::accept(Visitor& visitor) const {
    for (const Frame& frame : frames_) {
        if (frame.message()) { frame.message()->accept(visitor); }
    }
}

void Stream::print(std::ostream& out) const {
    out << "Stream{";
    out << "frames=";
    print::sequence(out, frames_);
    out << '}';
}

bool Stream::operator==(const Stream& other) const {
    return frames_ == other.frames_;
}

bool Stream::operator!=(const Stream& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& out, const Frame& frame) { frame.print(out); return out; }
std::ostream& operator<<(std::ostream& out, const Stream& stream) { stream.print(out); return out; }

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
