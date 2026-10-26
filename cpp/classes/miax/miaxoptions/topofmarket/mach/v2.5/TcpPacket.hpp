#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "messages/TcpMessage.hpp"
#include "structs/SesmPacketHeader.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class TcpMessageVisitor;

// The frame around one message: the sesm packet header and the message they select.
// Decode and encode here cover the headers; the packet decodes and encodes the message.
class TcpFrame {
  public:
    TcpFrame() = default;
    explicit TcpFrame(std::unique_ptr<TcpMessage> message);
    TcpFrame(const TcpFrame& other);
    TcpFrame& operator=(const TcpFrame& other);
    TcpFrame(TcpFrame&& other) noexcept = default;
    TcpFrame& operator=(TcpFrame&& other) noexcept = default;
    ~TcpFrame() = default;

    // Sesm Packet Header: SesM packet header
    const SesmPacketHeader& sesm_packet_header() const;
    SesmPacketHeader& sesm_packet_header();
    void set_sesm_packet_header(const SesmPacketHeader& value);

    // The message this frame carries, or null before one is set
    const TcpMessage* message() const;
    TcpMessage* message();
    void set_message(std::unique_ptr<TcpMessage> message);
    std::unique_ptr<TcpMessage> release();

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
    bool operator==(const TcpFrame& other) const;
    bool operator!=(const TcpFrame& other) const;

  private:
    SesmPacketHeader sesm_packet_header_{};
    std::unique_ptr<TcpMessage> message_;
    std::vector<std::byte> trailer_;
};

// A run of bytes off a TCP connection, read into the frames it holds. A read stops at
// the first frame the bytes do not hold in full and reports how many it consumed, so the
// caller keeps the remainder and presents it again with more bytes behind it.
class TcpPacket {
  public:
    TcpPacket() = default;

    // The frames, each holding one message
    const std::vector<TcpFrame>& frames() const;
    std::vector<TcpFrame>& frames();
    // Append a frame holding this message; the frame headers are derived on encode
    void add(std::unique_ptr<TcpMessage> message);

    // Read every whole frame in the bytes at data, and return how many bytes that took.
    // What is left is a frame the run does not hold in full: keep it and read it again
    // with the bytes that follow. Throws DecodeError only on a frame that cannot be read.
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write a whole packet to the bytes at data, and return how many were written; throws EncodeError
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    std::size_t encoded_size() const;
    // Hand every message, in order, to the visitor
    void accept(TcpMessageVisitor& visitor) const;
    void print(std::ostream& out) const;

    bool operator==(const TcpPacket& other) const;
    bool operator!=(const TcpPacket& other) const;

  private:
    std::vector<TcpFrame> frames_;
};

std::ostream& operator<<(std::ostream& out, const TcpFrame& frame);
std::ostream& operator<<(std::ostream& out, const TcpPacket& packet);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
