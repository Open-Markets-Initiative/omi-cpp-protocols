// Databento.MarketData.Normalized.Dbn.v2: GatewayStream.cpp
#include "GatewayStream.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

GatewayFrame::GatewayFrame(std::unique_ptr<GatewayMessage> message) : message_(std::move(message)) {}

GatewayFrame::GatewayFrame(const GatewayFrame& other)
  : record_header_(other.record_header_), message_(other.message_ ? other.message_->clone() : nullptr), trailer_(other.trailer_) {}

GatewayFrame& GatewayFrame::operator=(const GatewayFrame& other) {
    if (this != &other) {
        record_header_ = other.record_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
        trailer_ = other.trailer_;
    }
    return *this;
}

const RecordHeader& GatewayFrame::record_header() const { return record_header_; }
RecordHeader& GatewayFrame::record_header() { return record_header_; }
void GatewayFrame::set_record_header(const RecordHeader& value) { record_header_ = value; }

const GatewayMessage* GatewayFrame::message() const { return message_.get(); }
GatewayMessage* GatewayFrame::message() { return message_.get(); }
void GatewayFrame::set_message(std::unique_ptr<GatewayMessage> message) { message_ = std::move(message); }
std::unique_ptr<GatewayMessage> GatewayFrame::release() { return std::move(message_); }
const std::vector<std::byte>& GatewayFrame::trailer() const { return trailer_; }
std::vector<std::byte>& GatewayFrame::trailer() { return trailer_; }

std::size_t GatewayFrame::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += record_header_.decode(data + offset, length - offset);

    return offset;
}

std::size_t GatewayFrame::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("GatewayFrame", encoded_size(), capacity);

    offset += record_header_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t GatewayFrame::encoded_size() const {
    return record_header_.encoded_size();
}

void GatewayFrame::print(std::ostream& out) const {
    out << "GatewayFrame{";
    out << "record_header=";
    record_header_.print(out);
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool GatewayFrame::operator==(const GatewayFrame& other) const {
    if (!(record_header_ == other.record_header_)) { return false; }
    if (!(trailer_ == other.trailer_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool GatewayFrame::operator!=(const GatewayFrame& other) const { return !(*this == other); }

const Greeting& GatewayStream::greeting() const { return greeting_; }
Greeting& GatewayStream::greeting() { return greeting_; }
void GatewayStream::set_greeting(const Greeting& value) { greeting_ = value; }

const ChallengeRequest& GatewayStream::challenge_request() const { return challenge_request_; }
ChallengeRequest& GatewayStream::challenge_request() { return challenge_request_; }
void GatewayStream::set_challenge_request(const ChallengeRequest& value) { challenge_request_ = value; }

const AuthenticationResponse& GatewayStream::authentication_response() const { return authentication_response_; }
AuthenticationResponse& GatewayStream::authentication_response() { return authentication_response_; }
void GatewayStream::set_authentication_response(const AuthenticationResponse& value) { authentication_response_ = value; }

const Metadata& GatewayStream::metadata() const { return metadata_; }
Metadata& GatewayStream::metadata() { return metadata_; }
void GatewayStream::set_metadata(const Metadata& value) { metadata_ = value; }

const std::vector<GatewayFrame>& GatewayStream::frames() const { return frames_; }
std::vector<GatewayFrame>& GatewayStream::frames() { return frames_; }
void GatewayStream::add(std::unique_ptr<GatewayMessage> message) { frames_.emplace_back(std::move(message)); }

std::size_t GatewayStream::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    frames_.clear();

    offset += greeting_.decode(data + offset, length - offset);

    offset += challenge_request_.decode(data + offset, length - offset);

    offset += authentication_response_.decode(data + offset, length - offset);

    offset += metadata_.decode(data + offset, length - offset);

    while (offset < length) {
        const std::size_t start = offset;

        // A frame the run does not hold in full is the caller's tail, not a fault: stop
        // short of it and leave it out of what this read consumed.
        if (length - start < 16) { break; }

        GatewayFrame frame;
        offset += frame.decode(data + offset, length - offset);
        const std::size_t frame_size = wire::count(frame.record_header().record_length()) * 4;
        if (frame_size < 16) { throw DecodeError("GatewayStream", 16, frame_size); }
        if (start + frame_size > length) { offset = start; break; }
        const std::size_t body = start + frame_size - offset;
        std::unique_ptr<GatewayMessage> message = GatewayMessageFactory::create(frame.record_header().rtype());
        // What the message left of its frame: bytes the model does not describe, kept as they came
        const std::size_t used = message->decode(data + offset, body);
        frame.trailer().assign(data + offset + used, data + start + frame_size);
        offset = start + frame_size;
        frame.set_message(std::move(message));
        frames_.push_back(std::move(frame));
    }

    return offset;
}

std::size_t GatewayStream::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("GatewayStream", encoded_size(), capacity);

    auto greeting = greeting_;
    auto challenge_request = challenge_request_;
    auto authentication_response = authentication_response_;
    auto metadata = metadata_;

    offset += greeting.encode(data + offset, capacity - offset);

    offset += challenge_request.encode(data + offset, capacity - offset);

    offset += authentication_response.encode(data + offset, capacity - offset);

    offset += metadata.encode(data + offset, capacity - offset);

    for (const GatewayFrame& frame : frames_) {
        if (frame.message() == nullptr) { throw EncodeError("GatewayStream", "a frame holds no message"); }
        const std::size_t frame_size = frame.encoded_size() + frame.message()->encoded_size() + frame.trailer().size();

        auto record_header = frame.record_header();
        record_header.set_record_length(static_cast<std::uint8_t>((frame_size) / 4));
        record_header.set_rtype(frame.message()->type());

        offset += record_header.encode(data + offset, capacity - offset);

        offset += frame.message()->encode(data + offset, capacity - offset);
        wire::write_bytes(data + offset, frame.trailer().data(), frame.trailer().size());
        offset += frame.trailer().size();
    }

    return offset;
}

std::size_t GatewayStream::encoded_size() const {
    std::size_t total = greeting_.encoded_size() + challenge_request_.encoded_size() + authentication_response_.encoded_size() + metadata_.encoded_size();
    for (const GatewayFrame& frame : frames_) {
        total += frame.encoded_size() + (frame.message() ? frame.message()->encoded_size() : 0) + frame.trailer().size();
    }
    return total;
}

void GatewayStream::accept(GatewayMessageVisitor& visitor) const {
    for (const GatewayFrame& frame : frames_) {
        if (frame.message()) { frame.message()->accept(visitor); }
    }
}

void GatewayStream::print(std::ostream& out) const {
    out << "GatewayStream{";
    out << "greeting=";
    greeting_.print(out);
    out << ", challenge_request=";
    challenge_request_.print(out);
    out << ", authentication_response=";
    authentication_response_.print(out);
    out << ", metadata=";
    metadata_.print(out);
    out << ", frames=";
    print::sequence(out, frames_);
    out << '}';
}

bool GatewayStream::operator==(const GatewayStream& other) const {
    return greeting_ == other.greeting_ && challenge_request_ == other.challenge_request_ && authentication_response_ == other.authentication_response_ && metadata_ == other.metadata_ && frames_ == other.frames_;
}

bool GatewayStream::operator!=(const GatewayStream& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& out, const GatewayFrame& frame) { frame.print(out); return out; }
std::ostream& operator<<(std::ostream& out, const GatewayStream& stream) { stream.print(out); return out; }

} // namespace databento::marketdata::normalized::dbn::v2
