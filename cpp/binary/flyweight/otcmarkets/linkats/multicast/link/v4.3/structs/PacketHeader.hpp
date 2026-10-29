#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/PacketFlag.hpp"
#include "../common/Day.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

class PacketHeader {
  public:
    static constexpr const char* name = "PacketHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PacketHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PacketHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    std::uint16_t packet_size() const { return wire::read_u16_be(at(0)); }

    std::uint32_t seq_num() const { return wire::read_u32_be(at(2)); }

    PacketFlag packet_flag() const { return PacketFlag{ bytes_.subspan(6) }; }

    std::uint8_t message_count() const { return wire::read_u8(at(7)); }

    std::chrono::milliseconds packet_milli() const { return std::chrono::milliseconds(static_cast<std::int64_t>(wire::read_u32_be(at(8)))); }
    std::int64_t packet_milli_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(packet_milli().count()) * 1000000); }

    void print(std::ostream& out) const {
        out << "PacketHeader{";
        out << "packet_size=";
        out << packet_size();
        out << ", seq_num=";
        out << seq_num();
        out << ", packet_flag=";
        packet_flag().print(out);
        out << ", message_count=";
        out << static_cast<int>(message_count());
        out << ", packet_milli=";
        calendar::print(out, packet_milli().count(), 1000000, "America/New_York");
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

} // namespace otcmarkets::linkats::multicast::link::v4_3
