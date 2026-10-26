#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/EsesmPacketType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// ESesM packet header
class EsesmPacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 3;

    EsesmPacketHeader() = default;
    EsesmPacketHeader(std::uint16_t esesm_packet_length, EsesmPacketType esesm_packet_type);

    // Esesm Packet Length: The length of rest of the packet
    std::uint16_t esesm_packet_length() const;
    void set_esesm_packet_length(std::uint16_t value);

    // Esesm Packet Type: ESesM protocol packet type
    EsesmPacketType esesm_packet_type() const;
    void set_esesm_packet_type(EsesmPacketType value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const EsesmPacketHeader& other) const;
    bool operator!=(const EsesmPacketHeader& other) const;

  private:
    std::uint16_t esesm_packet_length_{};
    EsesmPacketType esesm_packet_type_{};
};

std::ostream& operator<<(std::ostream& out, const EsesmPacketHeader& value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
