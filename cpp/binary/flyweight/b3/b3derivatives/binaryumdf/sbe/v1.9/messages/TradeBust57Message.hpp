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

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// TradeBust_57Message
class TradeBust57Message {
  public:
    static constexpr const char* name = "TradeBust57Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeBust57Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeBust57Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 48;
    static constexpr std::size_t fixed_size = 48;
    std::size_t encoded_size() const { return 48; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    TradingSessionId trading_session_id() const { return static_cast<TradingSessionId>(wire::read_u8(at(9))); }

    std::span<const std::byte, 2> offset_10_padding_2() const { return bytes_.subspan(10).template first<2>(); }

    Decimal md_future_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(12))), -4); }

    std::int64_t md_entry_size_quantity() const { return wire::read_i64_le(at(20)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(28)); }

    std::uint16_t trade_date() const { return wire::read_u16_le(at(32)); }

    std::span<const std::byte, 2> offset_34_padding_2() const { return bytes_.subspan(34).template first<2>(); }

    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(36)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> rpt_seq() const { return wire::nullable(wire::read_u32_le(at(44)), static_cast<std::uint32_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "TradeBust57Message{";
        out << "security_id=";
        out << security_id();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", trading_session_id=";
        out << trading_session_id();
        out << ", offset_10_padding_2=";
        print::hex(out, offset_10_padding_2().data(), offset_10_padding_2().size());
        out << ", md_future_price=";
        out << md_future_price();
        out << ", md_entry_size_quantity=";
        out << md_entry_size_quantity();
        out << ", trade_id=";
        out << trade_id();
        out << ", trade_date=";
        out << trade_date();
        out << ", offset_34_padding_2=";
        print::hex(out, offset_34_padding_2().data(), offset_34_padding_2().size());
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

inline std::ostream& operator<<(std::ostream& out, const TradeBust57Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
