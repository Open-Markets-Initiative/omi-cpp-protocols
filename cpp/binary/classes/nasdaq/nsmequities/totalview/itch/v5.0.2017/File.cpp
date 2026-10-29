#include "File.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

FileFrame::FileFrame(std::unique_ptr<FileMessage> message) : message_(std::move(message)) {}

FileFrame::FileFrame(const FileFrame& other)
  : message_header_(other.message_header_), message_(other.message_ ? other.message_->clone() : nullptr), trailer_(other.trailer_) {}

FileFrame& FileFrame::operator=(const FileFrame& other) {
    if (this != &other) {
        message_header_ = other.message_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
        trailer_ = other.trailer_;
    }
    return *this;
}

const MessageHeader& FileFrame::message_header() const { return message_header_; }
MessageHeader& FileFrame::message_header() { return message_header_; }
void FileFrame::set_message_header(const MessageHeader& value) { message_header_ = value; }

const FileMessage* FileFrame::message() const { return message_.get(); }
FileMessage* FileFrame::message() { return message_.get(); }
void FileFrame::set_message(std::unique_ptr<FileMessage> message) { message_ = std::move(message); }
std::unique_ptr<FileMessage> FileFrame::release() { return std::move(message_); }
const std::vector<std::byte>& FileFrame::trailer() const { return trailer_; }
std::vector<std::byte>& FileFrame::trailer() { return trailer_; }

std::size_t FileFrame::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += message_header_.decode(data + offset, length - offset);

    return offset;
}

std::size_t FileFrame::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FileFrame", encoded_size(), capacity);

    offset += message_header_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t FileFrame::encoded_size() const {
    return message_header_.encoded_size();
}

void FileFrame::print(std::ostream& out) const {
    out << "FileFrame{";
    out << "message_header=";
    message_header_.print(out);
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    if (!trailer_.empty()) { out << ", trailer="; print::hex(out, trailer_.data(), trailer_.size()); }
    out << '}';
}

bool FileFrame::operator==(const FileFrame& other) const {
    if (!(message_header_ == other.message_header_)) { return false; }
    if (!(trailer_ == other.trailer_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool FileFrame::operator!=(const FileFrame& other) const { return !(*this == other); }

const std::vector<FileFrame>& File::frames() const { return frames_; }
std::vector<FileFrame>& File::frames() { return frames_; }
void File::add(std::unique_ptr<FileMessage> message) { frames_.emplace_back(std::move(message)); }

std::size_t File::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    frames_.clear();

    while (offset < length) {
        const std::size_t start = offset;

        // A frame the run does not hold in full is the caller's tail, not a fault: stop
        // short of it and leave it out of what this read consumed.
        if (length - start < 3) { break; }

        FileFrame frame;
        offset += frame.decode(data + offset, length - offset);
        const std::size_t frame_size = wire::count(frame.message_header().message_length()) + 2;
        if (frame_size < 3) { throw DecodeError("File", 3, frame_size); }
        if (start + frame_size > length) { offset = start; break; }
        const std::size_t body = start + frame_size - offset;
        std::unique_ptr<FileMessage> message = FileMessageFactory::create(frame.message_header().message_type());
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


    for (const FileFrame& frame : frames_) {
        if (frame.message() == nullptr) { throw EncodeError("File", "a frame holds no message"); }
        const std::size_t frame_size = frame.encoded_size() + frame.message()->encoded_size() + frame.trailer().size();

        auto message_header = frame.message_header();
        message_header.set_message_length(static_cast<std::uint16_t>(frame_size - 2));
        message_header.set_message_type(frame.message()->type());

        offset += message_header.encode(data + offset, capacity - offset);

        offset += frame.message()->encode(data + offset, capacity - offset);
        wire::write_bytes(data + offset, frame.trailer().data(), frame.trailer().size());
        offset += frame.trailer().size();
    }

    return offset;
}

std::size_t File::encoded_size() const {
    std::size_t total = 0;
    for (const FileFrame& frame : frames_) {
        total += frame.encoded_size() + (frame.message() ? frame.message()->encoded_size() : 0) + frame.trailer().size();
    }
    return total;
}

void File::accept(FileMessageVisitor& visitor) const {
    for (const FileFrame& frame : frames_) {
        if (frame.message()) { frame.message()->accept(visitor); }
    }
}

void File::print(std::ostream& out) const {
    out << "File{";
    out << "frames=";
    print::sequence(out, frames_);
    out << '}';
}

bool File::operator==(const File& other) const {
    return frames_ == other.frames_;
}

bool File::operator!=(const File& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& out, const FileFrame& frame) { frame.print(out); return out; }
std::ostream& operator<<(std::ostream& out, const File& stream) { stream.print(out); return out; }

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
