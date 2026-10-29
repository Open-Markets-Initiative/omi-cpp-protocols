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
#include "../enums/FastMarketIndicator.hpp"
#include "../groups/MdInstrumentEntryGrp.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Published for each instrument in one snapshot cycle, carrying instrument state information
// and trade statistics.
class InstrumentSummaryMessage {
  public:
    static constexpr const char* name = "InstrumentSummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrumentSummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrumentSummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 408;
    static constexpr std::size_t fixed_size = 408;
    std::size_t encoded_size() const { return 408; }

    std::int64_t security_id() const { return wire::read_i64_le(at(0)); }

    std::chrono::nanoseconds last_update_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(8)))); }

    std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(16)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::uint32_t tot_no_orders() const { return wire::read_u32_le(at(24)); }

    SecurityStatus security_status() const { return static_cast<SecurityStatus>(wire::read_u8(at(28))); }

    SecurityTradingStatus security_trading_status() const { return static_cast<SecurityTradingStatus>(wire::read_u8(at(29))); }

    FastMarketIndicator fast_market_indicator() const { return static_cast<FastMarketIndicator>(wire::read_u8(at(30))); }

    std::uint8_t no_md_entries() const { return wire::read_u8(at(31)); }

    std::int64_t trade_volume() const { return wire::read_i64_le(at(32)); }

    std::uint32_t no_of_trades() const { return wire::read_u32_le(at(40)); }

    std::span<const std::byte, 4> pad_4() const { return bytes_.subspan(44).template first<4>(); }

    view::entries<MdInstrumentEntryGrp> md_instrument_entry_grp() const { return view::entries<MdInstrumentEntryGrp>{ bytes_.subspan(48), 15 }; }

    void print(std::ostream& out) const {
        out << "InstrumentSummaryMessage{";
        out << "security_id=";
        out << security_id();
        out << ", last_update_time=";
        out << last_update_time().count();
        out << ", trd_reg_ts_execution_time=";
        print::optional_duration(out, trd_reg_ts_execution_time());
        out << ", tot_no_orders=";
        out << tot_no_orders();
        out << ", security_status=";
        out << security_status();
        out << ", security_trading_status=";
        out << security_trading_status();
        out << ", fast_market_indicator=";
        out << fast_market_indicator();
        out << ", no_md_entries=";
        out << static_cast<int>(no_md_entries());
        out << ", trade_volume=";
        out << trade_volume();
        out << ", no_of_trades=";
        out << no_of_trades();
        out << ", pad_4=";
        print::hex(out, pad_4().data(), pad_4().size());
        out << ", md_instrument_entry_grp=";
        print::sequence(out, md_instrument_entry_grp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrumentSummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
