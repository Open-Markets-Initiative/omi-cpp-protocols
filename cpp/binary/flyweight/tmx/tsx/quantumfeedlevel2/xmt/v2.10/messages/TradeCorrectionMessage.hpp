// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/TradeCorrectionMessage.hpp
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

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class TradeCorrectionMessage {
  public:
    static constexpr const char* name = "TradeCorrectionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeCorrectionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeCorrectionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 48;
    static constexpr std::size_t fixed_size = 48;
    std::size_t encoded_size() const { return 48; }

    std::string_view symbol() const { return view::text(at(0), 9, ' '); }

    std::optional<std::uint32_t> trade_number() const { return wire::nullable(wire::read_u32_le(at(9)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<Decimal> price() const { return wire::nullable_decimal(wire::read_u64_le(at(13)), static_cast<std::uint64_t>(0ULL), -6); }

    std::optional<std::uint32_t> volume() const { return wire::nullable(wire::read_u32_le(at(21)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint16_t> buy_broker_number() const { return wire::nullable(wire::read_u16_le(at(25)), static_cast<std::uint16_t>(0ULL)); }

    std::optional<std::uint16_t> sell_broker_number() const { return wire::nullable(wire::read_u16_le(at(27)), static_cast<std::uint16_t>(0ULL)); }

    InitiatedBy initiated_by() const { return static_cast<InitiatedBy>(wire::read_char(at(29))); }

    std::optional<std::uint32_t> orig_trade_number() const { return wire::nullable(wire::read_u32_le(at(30)), static_cast<std::uint32_t>(0ULL)); }

    Bypass bypass() const { return static_cast<Bypass>(wire::read_char(at(34))); }

    std::optional<std::uint32_t> trade_time_stamp() const { return wire::nullable(wire::read_u32_le(at(35)), static_cast<std::uint32_t>(0ULL)); }

    CrossType cross_type() const { return static_cast<CrossType>(wire::read_char(at(39))); }

    std::optional<std::chrono::microseconds> trading_system_time_stamp() const { return wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(at(40)), static_cast<std::uint64_t>(0ULL)); }

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

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
