#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/DeliveryFlag.hpp"
#include "../structs/SendTime.hpp"

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

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

    std::uint16_t packet_size() const { return wire::read_u16_le(at(0)); }

    DeliveryFlag delivery_flag() const { return static_cast<DeliveryFlag>(wire::read_u8(at(2))); }

    std::uint8_t message_count() const { return wire::read_u8(at(3)); }

    std::uint32_t sequence_number() const { return wire::read_u32_le(at(4)); }

    SendTime send_time() const { return SendTime{ bytes_.subspan(8) }; }

    void print(std::ostream& out) const {
        out << "PacketHeader{";
        out << "packet_size=";
        out << packet_size();
        out << ", delivery_flag=";
        out << delivery_flag();
        out << ", message_count=";
        out << static_cast<int>(message_count());
        out << ", sequence_number=";
        out << sequence_number();
        out << ", send_time=";
        send_time().print(out);
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

} // namespace nyse::arcaequities::bbo::xdp::v2_4_c
