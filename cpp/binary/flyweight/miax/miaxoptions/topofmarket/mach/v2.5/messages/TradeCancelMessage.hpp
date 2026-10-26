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

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// This is the message format that will be used to disseminate canceled Trades that are
// resulting from Trade cancellations or corrections on MIAX during the current trading
// session.
class TradeCancelMessage {
  public:
    static constexpr const char* name = "TradeCancelMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeCancelMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeCancelMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 22;
    static constexpr std::size_t fixed_size = 22;
    std::size_t encoded_size() const { return 22; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t product_id() const { return wire::read_u32_le(at(4)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(8)); }

    std::uint8_t correction_number() const { return wire::read_u8(at(12)); }

    Decimal trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_le(at(13))), -4); }

    std::uint32_t trade_size() const { return wire::read_u32_le(at(17)); }

    TradeCondition trade_condition() const { return static_cast<TradeCondition>(wire::read_char(at(21))); }

    void print(std::ostream& out) const {
        out << "TradeCancelMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", product_id=";
        out << product_id();
        out << ", trade_id=";
        out << trade_id();
        out << ", correction_number=";
        out << static_cast<int>(correction_number());
        out << ", trade_price=";
        out << trade_price();
        out << ", trade_size=";
        out << trade_size();
        out << ", trade_condition=";
        out << trade_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeCancelMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
