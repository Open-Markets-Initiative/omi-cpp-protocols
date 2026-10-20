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
#include "../bitfields/MatchEventIndicator.hpp"
#include "../enums/TradingSessionId.hpp"
#include "../common/Decimal.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// ExecutionStatistics_56Message
class ExecutionStatistics56Message {
  public:
    static constexpr const char* name = "ExecutionStatistics56Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExecutionStatistics56Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExecutionStatistics56Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 52;
    static constexpr std::size_t fixed_size = 52;
    std::size_t encoded_size() const { return 52; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    TradingSessionId trading_session_id() const { return static_cast<TradingSessionId>(wire::read_u8(at(9))); }

    std::uint16_t trade_date() const { return wire::read_u16_le(at(10)); }

    std::int64_t trade_volume() const { return wire::read_i64_le(at(12)); }

    std::optional<Decimal> vwap_px() const { return wire::nullable_decimal(wire::read_i64_le(at(20)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<Decimal> net_chg_prev_day() const { return wire::nullable_decimal(wire::read_i64_le(at(28)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8); }

    std::uint32_t number_of_trades() const { return wire::read_u32_le(at(36)); }

    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(40)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> rpt_seq() const { return wire::nullable(wire::read_u32_le(at(48)), static_cast<std::uint32_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "ExecutionStatistics56Message{";
        out << "security_id=";
        out << security_id();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", trading_session_id=";
        out << trading_session_id();
        out << ", trade_date=";
        out << trade_date();
        out << ", trade_volume=";
        out << trade_volume();
        out << ", vwap_px=";
        print::optional(out, vwap_px());
        out << ", net_chg_prev_day=";
        print::optional(out, net_chg_prev_day());
        out << ", number_of_trades=";
        out << number_of_trades();
        out << ", md_entry_timestamp=";
        print::optional_duration(out, md_entry_timestamp());
        out << ", rpt_seq=";
        print::optional(out, rpt_seq());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExecutionStatistics56Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
