#include "TcpPacket.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

TcpFrame::TcpFrame(std::unique_ptr<TcpMessage> message) : message_(std::move(message)) {}

TcpFrame::TcpFrame(const TcpFrame& other)
  : sesm_packet_header_(other.sesm_packet_header_), message_(other.message_ ? other.message_->clone() : nullptr), trailer_(other.trailer_) {}

TcpFrame& TcpFrame::operator=(const TcpFrame& other) {
    if (this != &other) {
        sesm_packet_header_ = other.sesm_packet_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
        trailer_ = other.trailer_;
    }
    return *this;
}

const SesmPacketHeader& TcpFrame::sesm_packet_header() const { return sesm_packet_header_; }
SesmPacketHeader& TcpFrame::sesm_packet_header() { return sesm_packet_header_; }
void TcpFrame::set_sesm_packet_header(const SesmPacketHeader& value) { sesm_packet_header_ = value; }

const TcpMessage* TcpFrame::message() const { return message_.get(); }
TcpMessage* TcpFrame::message() { return message_.get(); }
void TcpFrame::set_message(std::unique_ptr<TcpMessage> message) { message_ = std::move(message); }
std::unique_ptr<TcpMessage> TcpFrame::release() { return std::move(message_); }
const std::vector<std::byte>& TcpFrame::trailer() const { return trailer_; }
std::vector<std::byte>& TcpFrame::trailer() { return trailer_; }

std::size_t TcpFrame::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += sesm_packet_header_.decode(data + offset, length - offset);

    return offset;
}

std::size_t TcpFrame::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TcpFrame", encoded_size(), capacity);

    offset += sesm_packet_header_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t TcpFrame::encoded_size() const {
    return sesm_packet_header_.encoded_size();
}

void TcpFrame::print(std::ostream& out) const {
    out << "TcpFrame{";
    out << "sesm_packet_header=";
    sesm_packet_header_.print(out);
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool TcpFrame::operator==(const TcpFrame& other) const {
    if (!(sesm_packet_header_ == other.sesm_packet_header_)) { return false; }
    if (!(trailer_ == other.trailer_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool TcpFrame::operator!=(const TcpFrame& other) const { return !(*this == other); }

const std::vector<TcpFrame>& TcpPacket::frames() const { return frames_; }
std::vector<TcpFrame>& TcpPacket::frames() { return frames_; }
void TcpPacket::add(std::unique_ptr<TcpMessage> message) { frames_.emplace_back(std::move(message)); }

std::size_t TcpPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    frames_.clear();

    while (offset < length) {
        const std::size_t start = offset;

        // A frame the run does not hold in full is the caller's tail, not a fault: stop
        // short of it and leave it out of what this read consumed.
        if (length - start < 3) { break; }

        TcpFrame frame;
        offset += frame.decode(data + offset, length - offset);
        const std::size_t frame_size = wire::count(frame.sesm_packet_header().sesm_packet_length()) + 2;
        if (frame_size < 3) { throw DecodeError("TcpPacket", 3, frame_size); }
        if (start + frame_size > length) { offset = start; break; }
        const std::size_t body = start + frame_size - offset;
        std::unique_ptr<TcpMessage> message = TcpMessageFactory::create(frame.sesm_packet_header().sesm_packet_type());
        // What the message left of its frame: bytes the model does not describe, kept as they came
        const std::size_t used = message->decode(data + offset, body);
        frame.trailer().assign(data + offset + used, data + start + frame_size);
        offset = start + frame_size;
        frame.set_message(std::move(message));
        frames_.push_back(std::move(frame));
    }

    return offset;
}

std::size_t TcpPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TcpPacket", encoded_size(), capacity);


    for (const TcpFrame& frame : frames_) {
        if (frame.message() == nullptr) { throw EncodeError("TcpPacket", "a frame holds no message"); }
        const std::size_t frame_size = frame.encoded_size() + frame.message()->encoded_size() + frame.trailer().size();

        auto sesm_packet_header = frame.sesm_packet_header();
        sesm_packet_header.set_sesm_packet_length(static_cast<std::uint16_t>(frame_size - 2));
        sesm_packet_header.set_sesm_packet_type(frame.message()->type());

        offset += sesm_packet_header.encode(data + offset, capacity - offset);

        offset += frame.message()->encode(data + offset, capacity - offset);
        wire::write_bytes(data + offset, frame.trailer().data(), frame.trailer().size());
        offset += frame.trailer().size();
    }

    return offset;
}

std::size_t TcpPacket::encoded_size() const {
    std::size_t total = 0;
    for (const TcpFrame& frame : frames_) {
        total += frame.encoded_size() + (frame.message() ? frame.message()->encoded_size() : 0) + frame.trailer().size();
    }
    return total;
}

void TcpPacket::accept(TcpMessageVisitor& visitor) const {
    for (const TcpFrame& frame : frames_) {
        if (frame.message()) { frame.message()->accept(visitor); }
    }
}

void TcpPacket::print(std::ostream& out) const {
    out << "TcpPacket{";
    out << "frames=";
    print::sequence(out, frames_);
    out << '}';
}

bool TcpPacket::operator==(const TcpPacket& other) const {
    return frames_ == other.frames_;
}

bool TcpPacket::operator!=(const TcpPacket& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& out, const TcpFrame& frame) { frame.print(out); return out; }
std::ostream& operator<<(std::ostream& out, const TcpPacket& stream) { stream.print(out); return out; }

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
