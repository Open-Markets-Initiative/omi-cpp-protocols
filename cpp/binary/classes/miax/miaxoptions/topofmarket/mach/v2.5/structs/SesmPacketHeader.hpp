#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/SesmPacketType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// SesM packet header
class SesmPacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 3;

    SesmPacketHeader() = default;
    SesmPacketHeader(std::uint16_t sesm_packet_length, SesmPacketType sesm_packet_type);

    // Sesm Packet Length: The length of rest of the packet
    std::uint16_t sesm_packet_length() const;
    void set_sesm_packet_length(std::uint16_t value);

    // Sesm Packet Type: SesM protocol packet type
    SesmPacketType sesm_packet_type() const;
    void set_sesm_packet_type(SesmPacketType value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SesmPacketHeader& other) const;
    bool operator!=(const SesmPacketHeader& other) const;

  private:
    std::uint16_t sesm_packet_length_{};
    SesmPacketType sesm_packet_type_{};
};

std::ostream& operator<<(std::ostream& out, const SesmPacketHeader& value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
