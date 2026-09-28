#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/ClientPacketType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Packet header of a packet sent by the client
class ClientPacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 3;

    ClientPacketHeader() = default;
    ClientPacketHeader(std::uint16_t packet_length, ClientPacketType client_packet_type);

    // Packet Length: Length of data message not including this field
    std::uint16_t packet_length() const;
    void set_packet_length(std::uint16_t value);

    // Client Packet Type: Code identifying this packet type sent by the client
    ClientPacketType client_packet_type() const;
    void set_client_packet_type(ClientPacketType value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ClientPacketHeader& other) const;
    bool operator!=(const ClientPacketHeader& other) const;

  private:
    std::uint16_t packet_length_{};
    ClientPacketType client_packet_type_{};
};

std::ostream& operator<<(std::ostream& out, const ClientPacketHeader& value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
