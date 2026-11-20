// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/OrderPriceTimeAssignedTermsMessage.hpp
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
#include "../enums/OrderSide.hpp"
#include "../common/Decimal.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class OrderPriceTimeAssignedTermsMessage {
  public:
    static constexpr const char* name = "OrderPriceTimeAssignedTermsMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderPriceTimeAssignedTermsMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderPriceTimeAssignedTermsMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 48;
    static constexpr std::size_t fixed_size = 48;
    std::size_t encoded_size() const { return 48; }

    std::string_view symbol() const { return view::text(at(0), 9, ' '); }

    std::optional<std::uint16_t> broker_number() const { return wire::nullable(wire::read_u16_le(at(9)), static_cast<std::uint16_t>(0ULL)); }

    OrderSide order_side() const { return static_cast<OrderSide>(wire::read_char(at(11))); }

    std::optional<std::uint64_t> order_id() const { return wire::nullable(wire::read_u64_le(at(12)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<Decimal> price() const { return wire::nullable_decimal(wire::read_u64_le(at(20)), static_cast<std::uint64_t>(0ULL), -6); }

    std::optional<std::uint32_t> volume() const { return wire::nullable(wire::read_u32_le(at(28)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::chrono::microseconds> priority_time_stamp() const { return wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(at(32)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::chrono::microseconds> trading_system_time_stamp() const { return wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(at(40)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "OrderPriceTimeAssignedTermsMessage{";
        out << "symbol=";
        print::text(out, symbol());
        out << ", broker_number=";
        print::optional(out, broker_number());
        out << ", order_side=";
        out << order_side();
        out << ", order_id=";
        print::optional(out, order_id());
        out << ", price=";
        print::optional(out, price());
        out << ", volume=";
        print::optional(out, volume());
        out << ", priority_time_stamp=";
        print::optional_duration(out, priority_time_stamp());
        out << ", trading_system_time_stamp=";
        print::optional_duration(out, trading_system_time_stamp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderPriceTimeAssignedTermsMessage& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
