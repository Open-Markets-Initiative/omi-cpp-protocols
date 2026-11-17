// Databento.MarketData.Normalized.Dbn.v2: File.hpp
#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "messages/Message.hpp"
#include "structs/Metadata.hpp"
#include "structs/RecordHeader.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

class Visitor;

// The frame around one message: the record header and the message they select.
// Decode and encode here cover the headers; the packet decodes and encodes the message.
class Frame {
  public:
    Frame() = default;
    explicit Frame(std::unique_ptr<Message> message);
    Frame(const Frame& other);
    Frame& operator=(const Frame& other);
    Frame(Frame&& other) noexcept = default;
    Frame& operator=(Frame&& other) noexcept = default;
    ~Frame() = default;

    // Record Header: DBN common header of every record
    const RecordHeader& record_header() const;
    RecordHeader& record_header();
    void set_record_header(const RecordHeader& value);

    // The message this frame carries, or null before one is set
    const Message* message() const;
    Message* message();
    void set_message(std::unique_ptr<Message> message);
    std::unique_ptr<Message> release();

    // Bytes inside the frame's declared size after its message ends, which the model does not
    // describe. They are kept as they came and written back, so the frame still encodes to the
    // bytes it was read from.
    const std::vector<std::byte>& trailer() const;
    std::vector<std::byte>& trailer();

    // The frame headers only
    std::size_t decode(const std::byte* data, std::size_t length);
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    // Same headers, the same trailer and, both present, the same message
    bool operator==(const Frame& other) const;
    bool operator!=(const Frame& other) const;

  private:
    RecordHeader record_header_{};
    std::unique_ptr<Message> message_;
    std::vector<std::byte> trailer_;
};

// A run of bytes off a TCP connection, read into the frames it holds. A read stops at
// the first frame the bytes do not hold in full and reports how many it consumed, so the
// caller keeps the remainder and presents it again with more bytes behind it.
class File {
  public:
    File() = default;

    // Metadata: DBN metadata header, once at the start of a file or stream
    const Metadata& metadata() const;
    Metadata& metadata();
    void set_metadata(const Metadata& value);

    // The frames, each holding one message
    const std::vector<Frame>& frames() const;
    std::vector<Frame>& frames();
    // Append a frame holding this message; the frame headers are derived on encode
    void add(std::unique_ptr<Message> message);

    // Read every whole frame in the bytes at data, and return how many bytes that took.
    // What is left is a frame the run does not hold in full: keep it and read it again
    // with the bytes that follow. Throws DecodeError only on a frame that cannot be read.
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write a whole packet to the bytes at data, and return how many were written; throws EncodeError
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    std::size_t encoded_size() const;
    // Hand every message, in order, to the visitor
    void accept(Visitor& visitor) const;
    void print(std::ostream& out) const;

    bool operator==(const File& other) const;
    bool operator!=(const File& other) const;

  private:
    Metadata metadata_{};
    std::vector<Frame> frames_;
};

std::ostream& operator<<(std::ostream& out, const Frame& frame);
std::ostream& operator<<(std::ostream& out, const File& packet);

} // namespace databento::marketdata::normalized::dbn::v2
