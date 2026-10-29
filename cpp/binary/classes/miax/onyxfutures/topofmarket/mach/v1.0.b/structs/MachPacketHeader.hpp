#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/PacketType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Mach packet header (12 bytes)
class MachPacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 12;

    MachPacketHeader() = default;
    MachPacketHeader(std::uint64_t sequence_number, std::uint16_t packet_length, PacketType packet_type, std::uint8_t session_number);

    // Sequence Number: Sequence number of this data packet
    std::uint64_t sequence_number() const;
    void set_sequence_number(std::uint64_t value);

    // Packet Length: Length of the packet. This includes the header and application data
    std::uint16_t packet_length() const;
    void set_packet_length(std::uint16_t value);

    // Packet Type: protocol packet type
    PacketType packet_type() const;
    void set_packet_type(PacketType value);

    // Session Number: The Session this packet was generated from
    std::uint8_t session_number() const;
    void set_session_number(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MachPacketHeader& other) const;
    bool operator!=(const MachPacketHeader& other) const;

  private:
    std::uint64_t sequence_number_{};
    std::uint16_t packet_length_{};
    PacketType packet_type_{};
    std::uint8_t session_number_{};
};

std::ostream& operator<<(std::ostream& out, const MachPacketHeader& value);

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
