#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../enums/BuySellIndicator.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// This Options Trade Message is designed to provide execution details for normal match events
// involving non-displayable order types. (Note: There is a separate message for NASDAQ Option
// auction events.)
class OptionsTradeMessagesNonAuction {
  public:
    static constexpr const char* name = "OptionsTradeMessagesNonAuction";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsTradeMessagesNonAuction(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsTradeMessagesNonAuction has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 29;
    static constexpr std::size_t fixed_size = 29;
    std::size_t encoded_size() const { return 29; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    BuySellIndicator buy_sell_indicator() const { return static_cast<BuySellIndicator>(wire::read_char(at(8))); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(9)); }

    std::uint32_t cross_number() const { return wire::read_u32_be(at(13)); }

    std::uint32_t match_number() const { return wire::read_u32_be(at(17)); }

    Decimal price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(21))), -4); }

    std::uint32_t volume_long() const { return wire::read_u32_be(at(25)); }

    void print(std::ostream& out) const {
        out << "OptionsTradeMessagesNonAuction{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", buy_sell_indicator=";
        out << buy_sell_indicator();
        out << ", option_id=";
        out << option_id();
        out << ", cross_number=";
        out << cross_number();
        out << ", match_number=";
        out << match_number();
        out << ", price_long=";
        out << price_long();
        out << ", volume_long=";
        out << volume_long();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsTradeMessagesNonAuction& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
