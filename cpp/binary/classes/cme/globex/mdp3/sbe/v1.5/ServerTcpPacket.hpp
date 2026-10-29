#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "messages/ServerTcpMessage.hpp"
#include "structs/MessageHeader.hpp"
#include "structs/ServerTechnicalHeader.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

class ServerTcpMessageVisitor;

// The frame around one message: the server technical header and message header and the message they select.
// Decode and encode here cover the headers; the packet decodes and encodes the message.
class ServerTcpFrame {
  public:
    ServerTcpFrame() = default;
    explicit ServerTcpFrame(std::unique_ptr<ServerTcpMessage> message);
    ServerTcpFrame(const ServerTcpFrame& other);
    ServerTcpFrame& operator=(const ServerTcpFrame& other);
    ServerTcpFrame(ServerTcpFrame&& other) noexcept = default;
    ServerTcpFrame& operator=(ServerTcpFrame&& other) noexcept = default;
    ~ServerTcpFrame() = default;

    // Server Technical Header: Cme Technical Header sent by Cme to the firm
    const ServerTechnicalHeader& server_technical_header() const;
    ServerTechnicalHeader& server_technical_header();
    void set_server_technical_header(const ServerTechnicalHeader& value);

    // Message Header: Message Size followed by the Simple Binary Header
    const MessageHeader& message_header() const;
    MessageHeader& message_header();
    void set_message_header(const MessageHeader& value);

    // The message this frame carries, or null before one is set
    const ServerTcpMessage* message() const;
    ServerTcpMessage* message();
    void set_message(std::unique_ptr<ServerTcpMessage> message);
    std::unique_ptr<ServerTcpMessage> release();

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
    bool operator==(const ServerTcpFrame& other) const;
    bool operator!=(const ServerTcpFrame& other) const;

  private:
    ServerTechnicalHeader server_technical_header_{};
    MessageHeader message_header_{};
    std::unique_ptr<ServerTcpMessage> message_;
    std::vector<std::byte> trailer_;
};

// A run of bytes off a TCP connection, read into the frames it holds. A read stops at
// the first frame the bytes do not hold in full and reports how many it consumed, so the
// caller keeps the remainder and presents it again with more bytes behind it.
class ServerTcpPacket {
  public:
    ServerTcpPacket() = default;

    // The frames, each holding one message
    const std::vector<ServerTcpFrame>& frames() const;
    std::vector<ServerTcpFrame>& frames();
    // Append a frame holding this message; the frame headers are derived on encode
    void add(std::unique_ptr<ServerTcpMessage> message);

    // Read every whole frame in the bytes at data, and return how many bytes that took.
    // What is left is a frame the run does not hold in full: keep it and read it again
    // with the bytes that follow. Throws DecodeError only on a frame that cannot be read.
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write a whole packet to the bytes at data, and return how many were written; throws EncodeError
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    std::size_t encoded_size() const;
    // Hand every message, in order, to the visitor
    void accept(ServerTcpMessageVisitor& visitor) const;
    void print(std::ostream& out) const;

    bool operator==(const ServerTcpPacket& other) const;
    bool operator!=(const ServerTcpPacket& other) const;

  private:
    std::vector<ServerTcpFrame> frames_;
};

std::ostream& operator<<(std::ostream& out, const ServerTcpFrame& frame);
std::ostream& operator<<(std::ostream& out, const ServerTcpPacket& packet);

} // namespace cme::globex::mdp3::sbe::v1_5
