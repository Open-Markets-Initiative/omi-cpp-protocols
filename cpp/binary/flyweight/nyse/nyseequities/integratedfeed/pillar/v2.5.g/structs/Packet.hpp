#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/PacketHeader.hpp"

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

// Pillar common client udp packet
class Packet {
  public:
    static constexpr const char* name = "Packet";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Packet(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Packet has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    PacketHeader packet_header() const { return PacketHeader{ bytes_.subspan(0) }; }

    void print(std::ostream& out) const {
        out << "Packet{";
        out << "packet_header=";
        packet_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Packet& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g
