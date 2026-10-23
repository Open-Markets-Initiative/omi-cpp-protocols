#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"
#include "../enums/TradeType.hpp"
#include "../common/Decimal.hpp"
#include "../enums/OppositeSide.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// This message is sent whenever a resting order is matched with an open leg of a resting
// combination order in whole or in part
class CombinationOrderExecutedMessage {
  public:
    static constexpr const char* name = "CombinationOrderExecutedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CombinationOrderExecutedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CombinationOrderExecutedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 65;
    static constexpr std::size_t fixed_size = 65;
    std::size_t encoded_size() const { return 65; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    std::uint32_t tradeable_instrument_id() const { return wire::read_u32_be(at(6)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(10))); }

    std::uint64_t order_id() const { return wire::read_u64_be(at(11)); }

    std::uint32_t quantity_remaining() const { return wire::read_u32_be(at(19)); }

    TradeType trade_type() const { return static_cast<TradeType>(wire::read_char(at(23))); }

    std::uint64_t trade_id() const { return wire::read_u64_be(at(24)); }

    std::uint32_t executed_quantity() const { return wire::read_u32_be(at(32)); }

    Decimal trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(36))), -2); }

    std::uint32_t opposite_tradeable_instrument_id() const { return wire::read_u32_be(at(44)); }

    OppositeSide opposite_side() const { return static_cast<OppositeSide>(wire::read_char(at(48))); }

    std::uint64_t opposite_order_id() const { return wire::read_u64_be(at(49)); }

    std::uint64_t combination_trade_id() const { return wire::read_u64_be(at(57)); }

    void print(std::ostream& out) const {
        out << "CombinationOrderExecutedMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", trade_date=";
        out << trade_date();
        out << ", tradeable_instrument_id=";
        out << tradeable_instrument_id();
        out << ", side=";
        out << side();
        out << ", order_id=";
        out << order_id();
        out << ", quantity_remaining=";
        out << quantity_remaining();
        out << ", trade_type=";
        out << trade_type();
        out << ", trade_id=";
        out << trade_id();
        out << ", executed_quantity=";
        out << executed_quantity();
        out << ", trade_price=";
        out << trade_price();
        out << ", opposite_tradeable_instrument_id=";
        out << opposite_tradeable_instrument_id();
        out << ", opposite_side=";
        out << opposite_side();
        out << ", opposite_order_id=";
        out << opposite_order_id();
        out << ", combination_trade_id=";
        out << combination_trade_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CombinationOrderExecutedMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
