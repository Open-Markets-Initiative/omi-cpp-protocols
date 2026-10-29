#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/PacketType.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Mach packet header (12 bytes)
class MachPacketHeader {
  public:
    static constexpr const char* name = "MachPacketHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MachPacketHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MachPacketHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    std::uint64_t sequence_number() const { return wire::read_u64_le(at(0)); }

    std::uint16_t packet_length() const { return wire::read_u16_le(at(8)); }

    PacketType packet_type() const { return static_cast<PacketType>(wire::read_u8(at(10))); }

    std::uint8_t session_number() const { return wire::read_u8(at(11)); }

    void print(std::ostream& out) const {
        out << "MachPacketHeader{";
        out << "sequence_number=";
        out << sequence_number();
        out << ", packet_length=";
        out << packet_length();
        out << ", packet_type=";
        out << packet_type();
        out << ", session_number=";
        out << static_cast<int>(session_number());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MachPacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
