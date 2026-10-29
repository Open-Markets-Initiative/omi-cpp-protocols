#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/TradeCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// This is the message format that will be used to disseminate Trades that are resulting from
// executions on MIAX during the current trading session
class StrategyTradeMessage {
  public:
    static constexpr const char* name = "StrategyTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StrategyTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StrategyTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 41;
    static constexpr std::size_t fixed_size = 41;
    std::size_t encoded_size() const { return 41; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t strategy_id() const { return wire::read_u32_le(at(4)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(8)); }

    Decimal net_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(12))), -4); }

    std::uint32_t trade_size() const { return wire::read_u32_le(at(20)); }

    TradeCondition trade_condition() const { return static_cast<TradeCondition>(wire::read_char(at(24))); }

    std::span<const std::byte, 16> reserved_16() const { return bytes_.subspan(25).template first<16>(); }

    void print(std::ostream& out) const {
        out << "StrategyTradeMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", strategy_id=";
        out << strategy_id();
        out << ", trade_id=";
        out << trade_id();
        out << ", net_price=";
        out << net_price();
        out << ", trade_size=";
        out << trade_size();
        out << ", trade_condition=";
        out << trade_condition();
        out << ", reserved_16=";
        print::hex(out, reserved_16().data(), reserved_16().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const StrategyTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
