#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/BinaryPacketHeader.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Cme Mdp Packet
class UdpPacket {
  public:
    static constexpr const char* name = "UdpPacket";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UdpPacket(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UdpPacket has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    BinaryPacketHeader binary_packet_header() const { return BinaryPacketHeader{ bytes_.subspan(0) }; }

    void print(std::ostream& out) const {
        out << "UdpPacket{";
        out << "binary_packet_header=";
        binary_packet_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UdpPacket& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
