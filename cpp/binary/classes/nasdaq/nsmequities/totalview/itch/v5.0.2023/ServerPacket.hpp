#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "messages/ServerMessage.hpp"
#include "structs/ServerPacketHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class ServerMessageVisitor;

// The frame around one message: the server packet header and the message they select.
// Decode and encode here cover the headers; the packet decodes and encodes the message.
class ServerFrame {
  public:
    ServerFrame() = default;
    explicit ServerFrame(std::unique_ptr<ServerMessage> message);
    ServerFrame(const ServerFrame& other);
    ServerFrame& operator=(const ServerFrame& other);
    ServerFrame(ServerFrame&& other) noexcept = default;
    ServerFrame& operator=(ServerFrame&& other) noexcept = default;
    ~ServerFrame() = default;

    // Server Packet Header: Packet header of a packet sent by the server
    const ServerPacketHeader& server_packet_header() const;
    ServerPacketHeader& server_packet_header();
    void set_server_packet_header(const ServerPacketHeader& value);

    // The message this frame carries, or null before one is set
    const ServerMessage* message() const;
    ServerMessage* message();
    void set_message(std::unique_ptr<ServerMessage> message);
    std::unique_ptr<ServerMessage> release();

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
    bool operator==(const ServerFrame& other) const;
    bool operator!=(const ServerFrame& other) const;

  private:
    ServerPacketHeader server_packet_header_{};
    std::unique_ptr<ServerMessage> message_;
    std::vector<std::byte> trailer_;
};

// A run of bytes off a TCP connection, read into the frames it holds. A read stops at
// the first frame the bytes do not hold in full and reports how many it consumed, so the
// caller keeps the remainder and presents it again with more bytes behind it.
class ServerPacket {
  public:
    ServerPacket() = default;

    // The frames, each holding one message
    const std::vector<ServerFrame>& frames() const;
    std::vector<ServerFrame>& frames();
    // Append a frame holding this message; the frame headers are derived on encode
    void add(std::unique_ptr<ServerMessage> message);

    // Read every whole frame in the bytes at data, and return how many bytes that took.
    // What is left is a frame the run does not hold in full: keep it and read it again
    // with the bytes that follow. Throws DecodeError only on a frame that cannot be read.
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write a whole packet to the bytes at data, and return how many were written; throws EncodeError
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    std::size_t encoded_size() const;
    // Hand every message, in order, to the visitor
    void accept(ServerMessageVisitor& visitor) const;
    void print(std::ostream& out) const;

    bool operator==(const ServerPacket& other) const;
    bool operator!=(const ServerPacket& other) const;

  private:
    std::vector<ServerFrame> frames_;
};

std::ostream& operator<<(std::ostream& out, const ServerFrame& frame);
std::ostream& operator<<(std::ostream& out, const ServerPacket& packet);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
