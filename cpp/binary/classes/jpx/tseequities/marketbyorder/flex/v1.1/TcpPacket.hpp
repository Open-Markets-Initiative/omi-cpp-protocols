#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "messages/TcpMessage.hpp"
#include "structs/TcpPacketHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

class TcpMessageVisitor;

// A packet: the tcp packet header, and the one message they select. Decode reads a
// whole packet; encode writes one back, deriving its length and code from the message held.
class TcpPacket {
  public:
    TcpPacket() = default;
    explicit TcpPacket(std::unique_ptr<TcpMessage> message);
    TcpPacket(const TcpPacket& other);
    TcpPacket& operator=(const TcpPacket& other);
    TcpPacket(TcpPacket&& other) noexcept = default;
    TcpPacket& operator=(TcpPacket&& other) noexcept = default;
    ~TcpPacket() = default;

    // Tcp Packet Header: Jpx Flex Tcp packet header carrying length prefix and packet type
    // discriminator
    const TcpPacketHeader& tcp_packet_header() const;
    TcpPacketHeader& tcp_packet_header();
    void set_tcp_packet_header(const TcpPacketHeader& value);

    // The message this packet carries, or null before one is set
    const TcpMessage* message() const;
    TcpMessage* message();
    void set_message(std::unique_ptr<TcpMessage> message);
    std::unique_ptr<TcpMessage> release();

    // Read a whole packet from the bytes at data, and return how many were consumed; throws DecodeError
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write a whole packet to the bytes at data, and return how many were written; throws EncodeError
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    std::size_t encoded_size() const;
    // Hand the message to the visitor
    void accept(TcpMessageVisitor& visitor) const;
    void print(std::ostream& out) const;

    // Same headers and, both present, the same message
    bool operator==(const TcpPacket& other) const;
    bool operator!=(const TcpPacket& other) const;

  private:
    TcpPacketHeader tcp_packet_header_{};
    std::unique_ptr<TcpMessage> message_;
};

std::ostream& operator<<(std::ostream& out, const TcpPacket& packet);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
