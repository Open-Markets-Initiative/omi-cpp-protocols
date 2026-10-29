#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/LiquidityIndicator.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// An Order Executed Message denotes that all or part of an order has been executed
class OrderExecutedMessage {
  public:
    static constexpr const char* name = "OrderExecutedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 29;
    static constexpr std::size_t fixed_size = 29;
    std::size_t encoded_size() const { return 29; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t order_token() const { return wire::read_u32_be(at(8)); }

    std::uint32_t executed_quantity() const { return wire::read_u32_be(at(12)); }

    Decimal execution_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(16))), -1); }

    LiquidityIndicator liquidity_indicator() const { return static_cast<LiquidityIndicator>(wire::read_char(at(20))); }

    std::uint64_t match_number() const { return wire::read_u64_be(at(21)); }

    void print(std::ostream& out) const {
        out << "OrderExecutedMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "Asia/Tokyo");
        out << ", order_token=";
        out << order_token();
        out << ", executed_quantity=";
        out << executed_quantity();
        out << ", execution_price=";
        out << execution_price();
        out << ", liquidity_indicator=";
        out << liquidity_indicator();
        out << ", match_number=";
        out << match_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderExecutedMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
