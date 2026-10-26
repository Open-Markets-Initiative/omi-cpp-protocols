#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/MachPacketType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Mach packet header (12 bytes)
class MachPacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 12;

    MachPacketHeader() = default;
    MachPacketHeader(std::uint64_t sequence_number, std::uint16_t mach_packet_length, MachPacketType mach_packet_type, std::uint8_t session_number);

    // Sequence Number: For Symbol Update/Trading Status/System State refreshes this is the
    // original sequence number from the live feed; for Order Book refresh this is the last
    // sequence number on the live feed at the time of the refresh request.
    std::uint64_t sequence_number() const;
    void set_sequence_number(std::uint64_t value);

    // Mach Packet Length: Length of the packet
    std::uint16_t mach_packet_length() const;
    void set_mach_packet_length(std::uint16_t value);

    // Mach Packet Type: Mach packet type
    MachPacketType mach_packet_type() const;
    void set_mach_packet_type(MachPacketType value);

    // Session Number: protocol packet type
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
    std::uint16_t mach_packet_length_{};
    MachPacketType mach_packet_type_{};
    std::uint8_t session_number_{};
};

std::ostream& operator<<(std::ostream& out, const MachPacketHeader& value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
