#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "messages/Message.hpp"
#include "structs/MessageHeader.hpp"
#include "structs/PacketHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

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

    // Message Header: Jpx Flex tag header carrying length prefix and message type
    // discriminator
    const MessageHeader& message_header() const;
    MessageHeader& message_header();
    void set_message_header(const MessageHeader& value);

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
    MessageHeader message_header_{};
    std::unique_ptr<Message> message_;
    std::vector<std::byte> trailer_;
};

// A packet: the packet header, then either its messages, each in a frame, or one
// of the actions the packet header can announce instead. Decode reads a whole datagram;
// encode writes one back, deriving every count, length and code from the frames held.
class UdpPacket {
  public:
    // What the packet holds: messages, or an action announced by its header
    enum class Kind {
        Messages,                // the packet holds messages
    };

    UdpPacket() = default;

    // Packet Header: Jpx Flex 26 byte packet header
    const PacketHeader& packet_header() const;
    PacketHeader& packet_header();
    void set_packet_header(const PacketHeader& value);

    Kind kind() const;
    void set_kind(Kind value);

    // The frames, each holding one message
    const std::vector<Frame>& frames() const;
    std::vector<Frame>& frames();

    // Bytes after the last frame that the model does not account for — a pad or a
    // trailer the specification leaves out. They are kept as they came and written
    // back, so a packet carrying one still encodes to the bytes it was read from.
    const std::vector<std::byte>& trailer() const;
    std::vector<std::byte>& trailer();
    // Append a frame holding this message; the frame headers are derived on encode
    void add(std::unique_ptr<Message> message);

    // Read a whole packet from the bytes at data, and return how many were consumed; throws DecodeError
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write a whole packet to the bytes at data, and return how many were written; throws EncodeError
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    std::size_t encoded_size() const;
    // Hand every message, in order, to the visitor
    void accept(Visitor& visitor) const;
    void print(std::ostream& out) const;

    bool operator==(const UdpPacket& other) const;
    bool operator!=(const UdpPacket& other) const;

  private:
    PacketHeader packet_header_{};
    Kind kind_{ Kind::Messages };
    std::vector<Frame> frames_;
    std::vector<std::byte> trailer_;
};

std::string_view to_string(UdpPacket::Kind kind);
std::ostream& operator<<(std::ostream& out, UdpPacket::Kind kind);
std::ostream& operator<<(std::ostream& out, const Frame& frame);
std::ostream& operator<<(std::ostream& out, const UdpPacket& packet);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
