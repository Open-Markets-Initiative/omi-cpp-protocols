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
#include "../bitfields/TradeCondition.hpp"
#include "../common/Decimal.hpp"
#include "../enums/TrdSubType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// ForwardTrade_54Message
class ForwardTrade54Message {
  public:
    static constexpr const char* name = "ForwardTrade54Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ForwardTrade54Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ForwardTrade54Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 68;
    static constexpr std::size_t fixed_size = 68;
    std::size_t encoded_size() const { return 68; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    TradingSessionId trading_session_id() const { return static_cast<TradingSessionId>(wire::read_u8(at(9))); }

    TradeCondition trade_condition() const { return TradeCondition{ bytes_.subspan(10) }; }

    Decimal md_future_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(12))), -4); }

    std::int64_t md_entry_size_quantity() const { return wire::read_i64_le(at(20)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(28)); }

    std::optional<std::uint32_t> md_entry_buyer() const { return wire::nullable(wire::read_u32_le(at(32)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint32_t> md_entry_seller() const { return wire::nullable(wire::read_u32_le(at(36)), static_cast<std::uint32_t>(0ULL)); }

    std::uint16_t trade_date() const { return wire::read_u16_le(at(40)); }

    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(42)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> rpt_seq() const { return wire::nullable(wire::read_u32_le(at(50)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint16_t> seller_days() const { return wire::nullable(wire::read_u16_le(at(54)), static_cast<std::uint16_t>(0ULL)); }

    std::optional<Decimal> md_entry_interest_rate() const { return wire::nullable_decimal(wire::read_i64_le(at(56)), static_cast<std::int64_t>(0LL), -4); }

    std::optional<TrdSubType> trd_sub_type() const { return wire::nullable_enum<TrdSubType>(wire::read_u8(at(64)), static_cast<std::uint8_t>(0ULL)); }

    std::span<const std::byte, 3> padding_3() const { return bytes_.subspan(65).template first<3>(); }

    void print(std::ostream& out) const {
        out << "ForwardTrade54Message{";
        out << "security_id=";
        out << security_id();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", trading_session_id=";
        out << trading_session_id();
        out << ", trade_condition=";
        trade_condition().print(out);
        out << ", md_future_price=";
        out << md_future_price();
        out << ", md_entry_size_quantity=";
        out << md_entry_size_quantity();
        out << ", trade_id=";
        out << trade_id();
        out << ", md_entry_buyer=";
        print::optional(out, md_entry_buyer());
        out << ", md_entry_seller=";
        print::optional(out, md_entry_seller());
        out << ", trade_date=";
        out << trade_date();
        out << ", md_entry_timestamp=";
        print::optional_duration(out, md_entry_timestamp());
        out << ", rpt_seq=";
        print::optional(out, rpt_seq());
        out << ", seller_days=";
        print::optional(out, seller_days());
        out << ", md_entry_interest_rate=";
        print::optional(out, md_entry_interest_rate());
        out << ", trd_sub_type=";
        print::optional(out, trd_sub_type());
        out << ", padding_3=";
        print::hex(out, padding_3().data(), padding_3().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ForwardTrade54Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
