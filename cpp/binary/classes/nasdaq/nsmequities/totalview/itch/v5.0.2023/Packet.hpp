#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "messages/PacketMessage.hpp"
#include "structs/MessageHeader.hpp"
#include "structs/PacketHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class PacketMessageVisitor;

// The frame around one message: the message header and the message they select.
// Decode and encode here cover the headers; the packet decodes and encodes the message.
class PacketFrame {
  public:
    PacketFrame() = default;
    explicit PacketFrame(std::unique_ptr<PacketMessage> message);
    PacketFrame(const PacketFrame& other);
    PacketFrame& operator=(const PacketFrame& other);
    PacketFrame(PacketFrame&& other) noexcept = default;
    PacketFrame& operator=(PacketFrame&& other) noexcept = default;
    ~PacketFrame() = default;

    // Message Header: Mold Udp 64 Message Header
    const MessageHeader& message_header() const;
    MessageHeader& message_header();
    void set_message_header(const MessageHeader& value);

    // The message this frame carries, or null before one is set
    const PacketMessage* message() const;
    PacketMessage* message();
    void set_message(std::unique_ptr<PacketMessage> message);
    std::unique_ptr<PacketMessage> release();

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
    bool operator==(const PacketFrame& other) const;
    bool operator!=(const PacketFrame& other) const;

  private:
    MessageHeader message_header_{};
    std::unique_ptr<PacketMessage> message_;
    std::vector<std::byte> trailer_;
};

// A packet: the packet header, then either its messages, each in a frame, or one
// of the actions the packet header can announce instead. Decode reads a whole datagram;
// encode writes one back, deriving every count, length and code from the frames held.
class Packet {
  public:
    // What the packet holds: messages, or an action announced by its header
    enum class Kind {
        Messages,                // the packet holds messages
        Heartbeat,               // Heartbeat
        EndOfSession,            // End Of Session
    };

    Packet() = default;

    // Packet Header: Itch Mold Udp 64 Packet Header
    const PacketHeader& packet_header() const;
    PacketHeader& packet_header();
    void set_packet_header(const PacketHeader& value);

    Kind kind() const;
    void set_kind(Kind value);

    // The frames, each holding one message
    const std::vector<PacketFrame>& frames() const;
    std::vector<PacketFrame>& frames();

    // Bytes after the last frame that the model does not account for — a pad or a
    // trailer the specification leaves out. They are kept as they came and written
    // back, so a packet carrying one still encodes to the bytes it was read from.
    const std::vector<std::byte>& trailer() const;
    std::vector<std::byte>& trailer();
    // Append a frame holding this message; the frame headers are derived on encode
    void add(std::unique_ptr<PacketMessage> message);

    // Read a whole packet from the bytes at data, and return how many were consumed; throws DecodeError
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write a whole packet to the bytes at data, and return how many were written; throws EncodeError
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    std::size_t encoded_size() const;
    // Hand every message, in order, to the visitor
    void accept(PacketMessageVisitor& visitor) const;
    void print(std::ostream& out) const;

    bool operator==(const Packet& other) const;
    bool operator!=(const Packet& other) const;

  private:
    PacketHeader packet_header_{};
    Kind kind_{ Kind::Messages };
    std::vector<PacketFrame> frames_;
    std::vector<std::byte> trailer_;
};

std::string_view to_string(Packet::Kind kind);
std::ostream& operator<<(std::ostream& out, Packet::Kind kind);
std::ostream& operator<<(std::ostream& out, const PacketFrame& frame);
std::ostream& operator<<(std::ostream& out, const Packet& packet);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
