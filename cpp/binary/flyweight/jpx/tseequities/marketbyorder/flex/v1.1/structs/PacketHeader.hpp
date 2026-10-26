#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Jpx Flex 26 byte packet header
class PacketHeader {
  public:
    static constexpr const char* name = "PacketHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PacketHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PacketHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 26;
    static constexpr std::size_t fixed_size = 26;
    std::size_t encoded_size() const { return 26; }

    std::uint8_t multicast_group_number() const { return wire::read_u8(at(0)); }

    std::uint8_t number_of_system_reboots() const { return wire::read_u8(at(1)); }

    std::uint32_t sequence_number() const { return wire::read_u32_be(at(2)); }

    std::string_view issue_code() const { return view::text(at(6), 12, ' '); }

    std::uint32_t update_number() const { return wire::read_u32_be(at(18)); }

    std::uint8_t packet_number() const { return wire::read_u8(at(22)); }

    std::uint8_t total_number_of_packets() const { return wire::read_u8(at(23)); }

    std::uint8_t utility_flag() const { return wire::read_u8(at(24)); }

    std::uint8_t message_count() const { return wire::read_u8(at(25)); }

    void print(std::ostream& out) const {
        out << "PacketHeader{";
        out << "multicast_group_number=";
        out << static_cast<int>(multicast_group_number());
        out << ", number_of_system_reboots=";
        out << static_cast<int>(number_of_system_reboots());
        out << ", sequence_number=";
        out << sequence_number();
        out << ", issue_code=";
        print::text(out, issue_code());
        out << ", update_number=";
        out << update_number();
        out << ", packet_number=";
        out << static_cast<int>(packet_number());
        out << ", total_number_of_packets=";
        out << static_cast<int>(total_number_of_packets());
        out << ", utility_flag=";
        out << static_cast<int>(utility_flag());
        out << ", message_count=";
        out << static_cast<int>(message_count());
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

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
