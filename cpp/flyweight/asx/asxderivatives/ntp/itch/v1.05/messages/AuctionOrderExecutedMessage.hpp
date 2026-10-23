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

namespace asx::asxderivatives::ntp::itch::v1_05 {

// This message is sent when orders are executed in the auction at the open of the market
class AuctionOrderExecutedMessage {
  public:
    static constexpr const char* name = "AuctionOrderExecutedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionOrderExecutedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionOrderExecutedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 52;
    static constexpr std::size_t fixed_size = 52;
    std::size_t encoded_size() const { return 52; }

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

    std::uint64_t opposite_order_id() const { return wire::read_u64_be(at(44)); }

    void print(std::ostream& out) const {
        out << "AuctionOrderExecutedMessage{";
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
        out << ", opposite_order_id=";
        out << opposite_order_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionOrderExecutedMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
