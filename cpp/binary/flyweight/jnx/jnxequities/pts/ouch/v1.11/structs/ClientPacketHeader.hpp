#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ClientPacketType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Packet header of a packet sent by the client
class ClientPacketHeader {
  public:
    static constexpr const char* name = "ClientPacketHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ClientPacketHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ClientPacketHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    static constexpr std::size_t fixed_size = 3;
    std::size_t encoded_size() const { return 3; }

    std::uint16_t packet_length() const { return wire::read_u16_be(at(0)); }

    ClientPacketType client_packet_type() const { return static_cast<ClientPacketType>(wire::read_char(at(2))); }

    void print(std::ostream& out) const {
        out << "ClientPacketHeader{";
        out << "packet_length=";
        out << packet_length();
        out << ", client_packet_type=";
        out << client_packet_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ClientPacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
