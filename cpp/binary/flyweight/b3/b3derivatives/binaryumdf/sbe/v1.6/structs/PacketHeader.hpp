#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// B3 Mdp Packet Header
class PacketHeader {
  public:
    static constexpr const char* name = "PacketHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PacketHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PacketHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::uint8_t channel_id() const { return wire::read_u8(at(0)); }

    std::uint8_t packet_reserved() const { return wire::read_u8(at(1)); }

    std::uint16_t sequence_version() const { return wire::read_u16_le(at(2)); }

    std::uint32_t sequence_number() const { return wire::read_u32_le(at(4)); }

    std::chrono::nanoseconds sending_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(8)))); }

    void print(std::ostream& out) const {
        out << "PacketHeader{";
        out << "channel_id=";
        out << static_cast<int>(channel_id());
        out << ", packet_reserved=";
        out << static_cast<int>(packet_reserved());
        out << ", sequence_version=";
        out << sequence_version();
        out << ", sequence_number=";
        out << sequence_number();
        out << ", sending_time=";
        out << sending_time().count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
