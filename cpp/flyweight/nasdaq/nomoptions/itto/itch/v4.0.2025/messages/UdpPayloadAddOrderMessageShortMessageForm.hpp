#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MarketSide.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// For bandwidth efficiency reasons, this message can be published in either short or long
// format.
class UdpPayloadAddOrderMessageShortMessageForm {
  public:
    static constexpr const char* name = "UdpPayloadAddOrderMessageShortMessageForm";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UdpPayloadAddOrderMessageShortMessageForm(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UdpPayloadAddOrderMessageShortMessageForm has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::uint64_t order_reference_number() const { return wire::read_u64_be(at(8)); }

    MarketSide market_side() const { return static_cast<MarketSide>(wire::read_char(at(16))); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(17)); }

    Decimal price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(21))), -4); }

    std::uint16_t volume_short() const { return wire::read_u16_be(at(23)); }

    void print(std::ostream& out) const {
        out << "UdpPayloadAddOrderMessageShortMessageForm{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", order_reference_number=";
        out << order_reference_number();
        out << ", market_side=";
        out << market_side();
        out << ", option_id=";
        out << option_id();
        out << ", price_short=";
        out << price_short();
        out << ", volume_short=";
        out << volume_short();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UdpPayloadAddOrderMessageShortMessageForm& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
