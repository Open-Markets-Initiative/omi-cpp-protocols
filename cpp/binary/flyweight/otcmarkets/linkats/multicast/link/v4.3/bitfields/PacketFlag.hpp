#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Packet Flags
class PacketFlag {
  public:
    static constexpr const char* name = "PacketFlag";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PacketFlag(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool heartbeat() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool seq_num_reset() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    bool replay() const { return (raw() & static_cast<std::uint8_t>(0x40)) != 0; }

    bool test() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
        out << "PacketFlag{";
        out << "heartbeat=";
        out << (heartbeat() ? "true" : "false");
        out << ", seq_num_reset=";
        out << (seq_num_reset() ? "true" : "false");
        out << ", replay=";
        out << (replay() ? "true" : "false");
        out << ", test=";
        out << (test() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PacketFlag& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
