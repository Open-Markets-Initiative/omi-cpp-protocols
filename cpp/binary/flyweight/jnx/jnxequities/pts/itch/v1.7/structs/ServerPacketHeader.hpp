#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ServerPacketType.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

// Packet header of a packet sent by the server
class ServerPacketHeader {
  public:
    static constexpr const char* name = "ServerPacketHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ServerPacketHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ServerPacketHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    static constexpr std::size_t fixed_size = 3;
    std::size_t encoded_size() const { return 3; }

    std::uint16_t packet_length() const { return wire::read_u16_be(at(0)); }

    ServerPacketType server_packet_type() const { return static_cast<ServerPacketType>(wire::read_char(at(2))); }

    void print(std::ostream& out) const {
        out << "ServerPacketHeader{";
        out << "packet_length=";
        out << packet_length();
        out << ", server_packet_type=";
        out << server_packet_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ServerPacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::itch::v1_7
