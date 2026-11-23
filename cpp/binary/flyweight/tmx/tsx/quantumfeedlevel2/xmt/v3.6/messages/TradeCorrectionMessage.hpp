// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/TradeCorrectionMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/InitiatedBy.hpp"
#include "../enums/Bypass.hpp"
#include "../enums/CrossType.hpp"
#include "../enums/ListingMarket.hpp"
#include "../enums/ProductType.hpp"
#include "../enums/IsMidOnly.hpp"
#include "../enums/IsDark.hpp"
#include "../enums/IsConditional.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class TradeCorrectionMessage {
  public:
    static constexpr const char* name = "TradeCorrectionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeCorrectionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeCorrectionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 60;
    static constexpr std::size_t fixed_size = 60;
    std::size_t encoded_size() const { return 60; }

    std::string_view symbol() const { return view::text(at(0), 12, ' '); }

    std::optional<std::uint32_t> trade_number() const { return wire::nullable(wire::read_u32_le(at(12)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<Decimal> price() const { return wire::nullable_decimal(wire::read_u64_le(at(16)), static_cast<std::uint64_t>(0ULL), -6); }

    std::optional<std::uint32_t> volume() const { return wire::nullable(wire::read_u32_le(at(24)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint16_t> buy_broker_number() const { return wire::nullable(wire::read_u16_le(at(28)), static_cast<std::uint16_t>(0ULL)); }

    std::optional<std::uint16_t> sell_broker_number() const { return wire::nullable(wire::read_u16_le(at(30)), static_cast<std::uint16_t>(0ULL)); }

    InitiatedBy initiated_by() const { return static_cast<InitiatedBy>(wire::read_char(at(32))); }

    std::optional<std::uint32_t> orig_trade_number() const { return wire::nullable(wire::read_u32_le(at(33)), static_cast<std::uint32_t>(0ULL)); }

    Bypass bypass() const { return static_cast<Bypass>(wire::read_char(at(37))); }

    std::optional<std::uint32_t> trade_time_stamp() const { return wire::nullable(wire::read_u32_le(at(38)), static_cast<std::uint32_t>(0ULL)); }

    CrossType cross_type() const { return static_cast<CrossType>(wire::read_char(at(42))); }

    std::optional<std::chrono::nanoseconds> trading_system_time_stamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(43)), static_cast<std::uint64_t>(0ULL)); }

    ListingMarket listing_market() const { return static_cast<ListingMarket>(wire::read_char(at(51))); }

    ProductType product_type() const { return static_cast<ProductType>(wire::read_char(at(52))); }

    std::optional<std::uint32_t> trade_date() const { return wire::nullable(wire::read_u32_le(at(53)), static_cast<std::uint32_t>(0ULL)); }

    IsMidOnly is_mid_only() const { return static_cast<IsMidOnly>(wire::read_char(at(57))); }

    IsDark is_dark() const { return static_cast<IsDark>(wire::read_char(at(58))); }

    IsConditional is_conditional() const { return static_cast<IsConditional>(wire::read_char(at(59))); }

    void print(std::ostream& out) const {
        out << "TradeCorrectionMessage{";
        out << "symbol=";
        print::text(out, symbol());
        out << ", trade_number=";
        print::optional(out, trade_number());
        out << ", price=";
        print::optional(out, price());
        out << ", volume=";
        print::optional(out, volume());
        out << ", buy_broker_number=";
        print::optional(out, buy_broker_number());
        out << ", sell_broker_number=";
        print::optional(out, sell_broker_number());
        out << ", initiated_by=";
        out << initiated_by();
        out << ", orig_trade_number=";
        print::optional(out, orig_trade_number());
        out << ", bypass=";
        out << bypass();
        out << ", trade_time_stamp=";
        print::optional(out, trade_time_stamp());
        out << ", cross_type=";
        out << cross_type();
        out << ", trading_system_time_stamp=";
        print::optional_duration(out, trading_system_time_stamp());
        out << ", listing_market=";
        out << listing_market();
        out << ", product_type=";
        out << product_type();
        out << ", trade_date=";
        print::optional(out, trade_date());
        out << ", is_mid_only=";
        out << is_mid_only();
        out << ", is_dark=";
        out << is_dark();
        out << ", is_conditional=";
        out << is_conditional();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeCorrectionMessage& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
