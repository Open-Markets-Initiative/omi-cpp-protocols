#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/PacketType.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Jpx Flex Tcp packet header carrying length prefix and packet type discriminator
class TcpPacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 3;

    TcpPacketHeader() = default;
    TcpPacketHeader(std::uint16_t packet_length, PacketType packet_type);

    // Packet Length: Length of remaining bytes after this field
    std::uint16_t packet_length() const;
    void set_packet_length(std::uint16_t value);

    // Packet Type: First byte of the Tcp packet identifying the packet type used as dispatch
    // key
    PacketType packet_type() const;
    void set_packet_type(PacketType value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const TcpPacketHeader& other) const;
    bool operator!=(const TcpPacketHeader& other) const;

  private:
    std::uint16_t packet_length_{};
    PacketType packet_type_{};
};

std::ostream& operator<<(std::ostream& out, const TcpPacketHeader& value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
