#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../enums/MarketCondition.hpp"
#include "../enums/FastMarketIndicator.hpp"
#include "../enums/SecurityTradingEvent.hpp"
#include "../enums/SoldOutIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../enums/TesSecurityStatus.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

class InstrumentStateChange {
  public:
    static constexpr const char* name = "InstrumentStateChange";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrumentStateChange(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrumentStateChange has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 48;
    static constexpr std::size_t fixed_size = 48;
    std::size_t encoded_size() const { return 48; }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<SecurityStatus> security_status() const { return wire::nullable_enum<SecurityStatus>(wire::read_u8(at(8)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<SecurityTradingStatus> security_trading_status() const { return wire::nullable_enum<SecurityTradingStatus>(wire::read_u8(at(9)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<MarketCondition> market_condition() const { return wire::nullable_enum<MarketCondition>(wire::read_u8(at(10)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<FastMarketIndicator> fast_market_indicator() const { return wire::nullable_enum<FastMarketIndicator>(wire::read_u8(at(11)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<SecurityTradingEvent> security_trading_event() const { return wire::nullable_enum<SecurityTradingEvent>(wire::read_u8(at(12)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<SoldOutIndicator> sold_out_indicator() const { return wire::nullable_enum<SoldOutIndicator>(wire::read_u8(at(13)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 2> pad2() const { return bytes_.subspan(14).template first<2>(); }

    std::optional<Decimal> high_px() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<Decimal> low_px() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(32)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<TesSecurityStatus> tes_security_status() const { return wire::nullable_enum<TesSecurityStatus>(wire::read_u8(at(40)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 7> pad7() const { return bytes_.subspan(41).template first<7>(); }

    void print(std::ostream& out) const {
        out << "InstrumentStateChange{";
        out << "security_id=";
        print::optional(out, security_id());
        out << ", security_status=";
        print::optional(out, security_status());
        out << ", security_trading_status=";
        print::optional(out, security_trading_status());
        out << ", market_condition=";
        print::optional(out, market_condition());
        out << ", fast_market_indicator=";
        print::optional(out, fast_market_indicator());
        out << ", security_trading_event=";
        print::optional(out, security_trading_event());
        out << ", sold_out_indicator=";
        print::optional(out, sold_out_indicator());
        out << ", pad2=";
        print::hex(out, pad2().data(), pad2().size());
        out << ", high_px=";
        print::optional(out, high_px());
        out << ", low_px=";
        print::optional(out, low_px());
        out << ", transact_time=";
        print::optional_duration(out, transact_time());
        out << ", tes_security_status=";
        print::optional(out, tes_security_status());
        out << ", pad7=";
        print::hex(out, pad7().data(), pad7().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrumentStateChange& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v13_0
