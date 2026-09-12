#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "messages/Message.hpp"
#include "structs/MessageHeader.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

class Visitor;

// The frame around one message: the message header and the message they select.
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

    // Message Header: Snap message header
    const MessageHeader& message_header() const;
    MessageHeader& message_header();
    void set_message_header(const MessageHeader& value);

    // The message this frame carries, or null before one is set
    const Message* message() const;
    Message* message();
    void set_message(std::unique_ptr<Message> message);
    std::unique_ptr<Message> release();

    // The frame headers only
    std::size_t decode(const std::byte* data, std::size_t length);
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    // Same headers and, both present, the same message
    bool operator==(const Frame& other) const;
    bool operator!=(const Frame& other) const;

  private:
    MessageHeader message_header_{};
    std::unique_ptr<Message> message_;
};

// A run of bytes off a TCP connection, read into the frames it holds. A read stops at
// the first frame the bytes do not hold in full and reports how many it consumed, so the
// caller keeps the remainder and presents it again with more bytes behind it.
class Stream {
  public:
    Stream() = default;

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

    bool operator==(const Stream& other) const;
    bool operator!=(const Stream& other) const;

  private:
    std::vector<Frame> frames_;
};

std::ostream& operator<<(std::ostream& out, const Frame& frame);
std::ostream& operator<<(std::ostream& out, const Stream& packet);

} // namespace iex::iexequities::deepplus::snap::v1_05
