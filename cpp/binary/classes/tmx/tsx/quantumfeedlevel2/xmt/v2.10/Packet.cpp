// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: Packet.cpp
#include "Packet.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

Frame::Frame(std::unique_ptr<Message> message) : message_(std::move(message)) {}

Frame::Frame(const Frame& other)
  : body_header_(other.body_header_), business_header_(other.business_header_), message_(other.message_ ? other.message_->clone() : nullptr), trailer_(other.trailer_) {}

Frame& Frame::operator=(const Frame& other) {
    if (this != &other) {
        body_header_ = other.body_header_;
        business_header_ = other.business_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
        trailer_ = other.trailer_;
    }
    return *this;
}

const BodyHeader& Frame::body_header() const { return body_header_; }
BodyHeader& Frame::body_header() { return body_header_; }
void Frame::set_body_header(const BodyHeader& value) { body_header_ = value; }

const BusinessHeader& Frame::business_header() const { return business_header_; }
BusinessHeader& Frame::business_header() { return business_header_; }
void Frame::set_business_header(const BusinessHeader& value) { business_header_ = value; }

const Message* Frame::message() const { return message_.get(); }
Message* Frame::message() { return message_.get(); }
void Frame::set_message(std::unique_ptr<Message> message) { message_ = std::move(message); }
std::unique_ptr<Message> Frame::release() { return std::move(message_); }
const std::vector<std::byte>& Frame::trailer() const { return trailer_; }
std::vector<std::byte>& Frame::trailer() { return trailer_; }

std::size_t Frame::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += body_header_.decode(data + offset, length - offset);

    offset += business_header_.decode(data + offset, length - offset);

    return offset;
}

std::size_t Frame::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Frame", encoded_size(), capacity);

    offset += body_header_.encode(data + offset, capacity - offset);

    offset += business_header_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t Frame::encoded_size() const {
    return body_header_.encoded_size() + business_header_.encoded_size();
}

void Frame::print(std::ostream& out) const {
    out << "Frame{";
    out << "body_header=";
    body_header_.print(out);
    out << ", ";
    out << "business_header=";
    business_header_.print(out);
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool Frame::operator==(const Frame& other) const {
    if (!(body_header_ == other.body_header_)) { return false; }
    if (!(business_header_ == other.business_header_)) { return false; }
    if (!(trailer_ == other.trailer_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool Frame::operator!=(const Frame& other) const { return !(*this == other); }

const FrameHeader& Packet::frame_header() const { return frame_header_; }
FrameHeader& Packet::frame_header() { return frame_header_; }
void Packet::set_frame_header(const FrameHeader& value) { frame_header_ = value; }

const std::optional<HeartbeatBody>& Packet::heartbeat_body() const { return heartbeat_body_; }
std::optional<HeartbeatBody>& Packet::heartbeat_body() { return heartbeat_body_; }

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
    heartbeat_body_.reset();

    offset += frame_header_.decode(data + offset, length - offset);

    if (!(frame_header_.message_length() > 6)) {
        kind_ = Kind::Empty;
        trailer_.assign(data + offset, data + length);
        return length;
    }

    wire::require("Packet", offset + 3, length);

    if (static_cast<char>(wire::read_u8(data + offset + 2)) == '0') {
        kind_ = Kind::HeartbeatBody;
        heartbeat_body_.emplace();
        heartbeat_body_->set_parent(this);
        offset += heartbeat_body_->decode(data + offset, length - offset);
        trailer_.assign(data + offset, data + length);
        return length;
    }

    kind_ = Kind::Messages;

    const std::size_t count = wire::count(frame_header_.num_body());

    for (std::size_t index = 0; index < count; ++index) {
        const std::size_t start = offset;
        Frame frame;
        offset += frame.decode(data + offset, length - offset);
        const std::size_t frame_size = wire::count(frame.body_header().msg_length());
        wire::require("Packet", start + frame_size, length);
        const std::size_t body = start + frame_size - offset;
        std::unique_ptr<Message> message = Factory::create(frame.body_header().msg_type());
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

    auto frame_header = frame_header_;
    if (kind_ == Kind::Messages) { frame_header.set_num_body(static_cast<std::uint8_t>(frames_.size())); }
    if (kind_ == Kind::HeartbeatBody && heartbeat_body_) { frame_header.set_num_body(static_cast<std::uint8_t>(heartbeat_body_->admin_body().size())); }
    frame_header.set_message_length(static_cast<std::uint16_t>(encoded_size() - 5));

    offset += frame_header.encode(data + offset, capacity - offset);

    if (kind_ == Kind::Empty) {
        wire::write_bytes(data + offset, trailer_.data(), trailer_.size());
        return offset + trailer_.size();
    }

    if (kind_ == Kind::HeartbeatBody) {
        if (!heartbeat_body_) { throw EncodeError("Packet", "a Heartbeat Body packet holds no Heartbeat Body"); }
        offset += heartbeat_body_->encode(data + offset, capacity - offset);
        wire::write_bytes(data + offset, trailer_.data(), trailer_.size());
        return offset + trailer_.size();
    }

    if (kind_ != Kind::Messages) { return offset; }

    for (const Frame& frame : frames_) {
        if (frame.message() == nullptr) { throw EncodeError("Packet", "a frame holds no message"); }
        const std::size_t frame_size = frame.encoded_size() + frame.message()->encoded_size() + frame.trailer().size();

        auto body_header = frame.body_header();
        auto business_header = frame.business_header();
        body_header.set_msg_length(static_cast<std::uint16_t>(frame_size));
        body_header.set_msg_type(frame.message()->type());

        offset += body_header.encode(data + offset, capacity - offset);

        offset += business_header.encode(data + offset, capacity - offset);

        offset += frame.message()->encode(data + offset, capacity - offset);
        wire::write_bytes(data + offset, frame.trailer().data(), frame.trailer().size());
        offset += frame.trailer().size();
    }

    wire::write_bytes(data + offset, trailer_.data(), trailer_.size());
    offset += trailer_.size();

    return offset;
}

std::size_t Packet::encoded_size() const {
    std::size_t total = frame_header_.encoded_size();
    if (kind_ == Kind::Empty) { return total + trailer_.size(); }
    if (kind_ == Kind::HeartbeatBody) { return total + (heartbeat_body_ ? heartbeat_body_->encoded_size() : 0) + trailer_.size(); }
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
    out << ", frame_header=";
    frame_header_.print(out);
    if (heartbeat_body_) { out << ", heartbeat_body="; heartbeat_body_->print(out); }
    out << ", frames=";
    print::sequence(out, frames_);
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool Packet::operator==(const Packet& other) const {
    return kind_ == other.kind_ && frame_header_ == other.frame_header_ && heartbeat_body_ == other.heartbeat_body_ && frames_ == other.frames_ && trailer_ == other.trailer_;
}

bool Packet::operator!=(const Packet& other) const { return !(*this == other); }

std::string_view to_string(Packet::Kind kind) {
    switch (kind) {
        case Packet::Kind::Messages: return "Messages";
        case Packet::Kind::HeartbeatBody: return "HeartbeatBody";
        case Packet::Kind::Empty: return "Empty";
        default: return "?";
    }
}

std::ostream& operator<<(std::ostream& out, Packet::Kind kind) { return out << to_string(kind); }
std::ostream& operator<<(std::ostream& out, const Frame& frame) { frame.print(out); return out; }
std::ostream& operator<<(std::ostream& out, const Packet& packet) { packet.print(out); return out; }

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
