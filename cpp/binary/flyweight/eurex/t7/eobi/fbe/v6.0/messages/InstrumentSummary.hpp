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
#include "../groups/MdInstrumentEntryGrpComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

class InstrumentSummary {
  public:
    static constexpr const char* name = "InstrumentSummary";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrumentSummary(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrumentSummary has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 272;
    static constexpr std::size_t fixed_size = 272;
    std::size_t encoded_size() const { return 272; }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<std::chrono::nanoseconds> last_update_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(16)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::uint16_t> tot_no_orders() const { return wire::nullable(wire::read_u16_le(at(24)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::optional<SecurityStatus> security_status() const { return wire::nullable_enum<SecurityStatus>(wire::read_u8(at(26)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<SecurityTradingStatus> security_trading_status() const { return wire::nullable_enum<SecurityTradingStatus>(wire::read_u8(at(27)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<MarketCondition> market_condition() const { return wire::nullable_enum<MarketCondition>(wire::read_u8(at(28)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<FastMarketIndicator> fast_market_indicator() const { return wire::nullable_enum<FastMarketIndicator>(wire::read_u8(at(29)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<SecurityTradingEvent> security_trading_event() const { return wire::nullable_enum<SecurityTradingEvent>(wire::read_u8(at(30)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<std::uint8_t> no_md_entries() const { return wire::nullable(wire::read_u8(at(31)), static_cast<std::uint8_t>(0xFFULL)); }

    view::entries<MdInstrumentEntryGrpComp> md_instrument_entry_grp_comp() const { return view::entries<MdInstrumentEntryGrpComp>{ bytes_.subspan(32), 15 }; }

    void print(std::ostream& out) const {
        out << "InstrumentSummary{";
        out << "security_id=";
        print::optional(out, security_id());
        out << ", last_update_time=";
        print::optional_duration(out, last_update_time());
        out << ", trd_reg_ts_execution_time=";
        print::optional_duration(out, trd_reg_ts_execution_time());
        out << ", tot_no_orders=";
        print::optional(out, tot_no_orders());
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
        out << ", no_md_entries=";
        print::optional(out, no_md_entries());
        out << ", md_instrument_entry_grp_comp=";
        print::sequence(out, md_instrument_entry_grp_comp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrumentSummary& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v6_0
