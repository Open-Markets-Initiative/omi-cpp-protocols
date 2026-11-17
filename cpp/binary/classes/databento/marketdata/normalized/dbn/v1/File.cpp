// Databento.MarketData.Normalized.Dbn.v1: File.cpp
#include "File.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

Frame::Frame(std::unique_ptr<Message> message) : message_(std::move(message)) {}

Frame::Frame(const Frame& other)
  : record_header_(other.record_header_), message_(other.message_ ? other.message_->clone() : nullptr), trailer_(other.trailer_) {}

Frame& Frame::operator=(const Frame& other) {
    if (this != &other) {
        record_header_ = other.record_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
        trailer_ = other.trailer_;
    }
    return *this;
}

const RecordHeader& Frame::record_header() const { return record_header_; }
RecordHeader& Frame::record_header() { return record_header_; }
void Frame::set_record_header(const RecordHeader& value) { record_header_ = value; }

const Message* Frame::message() const { return message_.get(); }
Message* Frame::message() { return message_.get(); }
void Frame::set_message(std::unique_ptr<Message> message) { message_ = std::move(message); }
std::unique_ptr<Message> Frame::release() { return std::move(message_); }
const std::vector<std::byte>& Frame::trailer() const { return trailer_; }
std::vector<std::byte>& Frame::trailer() { return trailer_; }

std::size_t Frame::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += record_header_.decode(data + offset, length - offset);

    return offset;
}

std::size_t Frame::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Frame", encoded_size(), capacity);

    offset += record_header_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t Frame::encoded_size() const {
    return record_header_.encoded_size();
}

void Frame::print(std::ostream& out) const {
    out << "Frame{";
    out << "record_header=";
    record_header_.print(out);
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool Frame::operator==(const Frame& other) const {
    if (!(record_header_ == other.record_header_)) { return false; }
    if (!(trailer_ == other.trailer_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool Frame::operator!=(const Frame& other) const { return !(*this == other); }

const Metadata& File::metadata() const { return metadata_; }
Metadata& File::metadata() { return metadata_; }
void File::set_metadata(const Metadata& value) { metadata_ = value; }

const std::vector<Frame>& File::frames() const { return frames_; }
std::vector<Frame>& File::frames() { return frames_; }
void File::add(std::unique_ptr<Message> message) { frames_.emplace_back(std::move(message)); }

std::size_t File::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    frames_.clear();

    offset += metadata_.decode(data + offset, length - offset);

    while (offset < length) {
        const std::size_t start = offset;

        // A frame the run does not hold in full is the caller's tail, not a fault: stop
        // short of it and leave it out of what this read consumed.
        if (length - start < 16) { break; }

        Frame frame;
        offset += frame.decode(data + offset, length - offset);
        const std::size_t frame_size = wire::count(frame.record_header().record_length()) * 4;
        if (frame_size < 16) { throw DecodeError("File", 16, frame_size); }
        if (start + frame_size > length) { offset = start; break; }
        const std::size_t body = start + frame_size - offset;
        std::unique_ptr<Message> message = Factory::create(frame.record_header().rtype());
        // What the message left of its frame: bytes the model does not describe, kept as they came
        const std::size_t used = message->decode(data + offset, body);
        frame.trailer().assign(data + offset + used, data + start + frame_size);
        offset = start + frame_size;
        frame.set_message(std::move(message));
        frames_.push_back(std::move(frame));
    }

    return offset;
}

std::size_t File::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("File", encoded_size(), capacity);

    auto metadata = metadata_;

    offset += metadata.encode(data + offset, capacity - offset);

    for (const Frame& frame : frames_) {
        if (frame.message() == nullptr) { throw EncodeError("File", "a frame holds no message"); }
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

std::size_t File::encoded_size() const {
    std::size_t total = metadata_.encoded_size();
    for (const Frame& frame : frames_) {
        total += frame.encoded_size() + (frame.message() ? frame.message()->encoded_size() : 0) + frame.trailer().size();
    }
    return total;
}

void File::accept(Visitor& visitor) const {
    for (const Frame& frame : frames_) {
        if (frame.message()) { frame.message()->accept(visitor); }
    }
}

void File::print(std::ostream& out) const {
    out << "File{";
    out << "metadata=";
    metadata_.print(out);
    out << ", frames=";
    print::sequence(out, frames_);
    out << '}';
}

bool File::operator==(const File& other) const {
    return metadata_ == other.metadata_ && frames_ == other.frames_;
}

bool File::operator!=(const File& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& out, const Frame& frame) { frame.print(out); return out; }
std::ostream& operator<<(std::ostream& out, const File& stream) { stream.print(out); return out; }

} // namespace databento::marketdata::normalized::dbn::v1
