// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/TradeCorrectionTermsMessage.hpp
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
#include "../enums/NonResident.hpp"
#include "../enums/SettlementTerms.hpp"
#include "../enums/CrossType.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class TradeCorrectionTermsMessage {
  public:
    static constexpr const char* name = "TradeCorrectionTermsMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeCorrectionTermsMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeCorrectionTermsMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 53;
    static constexpr std::size_t fixed_size = 53;
    std::size_t encoded_size() const { return 53; }

    std::string_view symbol() const { return view::text(at(0), 9, ' '); }

    std::optional<std::uint32_t> trade_number() const { return wire::nullable(wire::read_u32_le(at(9)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<Decimal> price() const { return wire::nullable_decimal(wire::read_u64_le(at(13)), static_cast<std::uint64_t>(0ULL), -6); }

    std::optional<std::uint32_t> volume() const { return wire::nullable(wire::read_u32_le(at(21)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint16_t> buy_broker_number() const { return wire::nullable(wire::read_u16_le(at(25)), static_cast<std::uint16_t>(0ULL)); }

    std::optional<std::uint16_t> sell_broker_number() const { return wire::nullable(wire::read_u16_le(at(27)), static_cast<std::uint16_t>(0ULL)); }

    InitiatedBy initiated_by() const { return static_cast<InitiatedBy>(wire::read_char(at(29))); }

    std::optional<std::uint32_t> orig_trade_number() const { return wire::nullable(wire::read_u32_le(at(30)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint32_t> trade_time_stamp() const { return wire::nullable(wire::read_u32_le(at(34)), static_cast<std::uint32_t>(0ULL)); }

    NonResident non_resident() const { return static_cast<NonResident>(wire::read_char(at(38))); }

    SettlementTerms settlement_terms() const { return static_cast<SettlementTerms>(wire::read_char(at(39))); }

    std::optional<std::uint32_t> settlement_date() const { return wire::nullable(wire::read_u32_le(at(40)), static_cast<std::uint32_t>(0ULL)); }

    CrossType cross_type() const { return static_cast<CrossType>(wire::read_char(at(44))); }

    std::optional<std::chrono::microseconds> trading_system_time_stamp() const { return wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(at(45)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "TradeCorrectionTermsMessage{";
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
        out << ", trade_time_stamp=";
        print::optional(out, trade_time_stamp());
        out << ", non_resident=";
        out << non_resident();
        out << ", settlement_terms=";
        out << settlement_terms();
        out << ", settlement_date=";
        print::optional(out, settlement_date());
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

inline std::ostream& operator<<(std::ostream& out, const TradeCorrectionTermsMessage& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
