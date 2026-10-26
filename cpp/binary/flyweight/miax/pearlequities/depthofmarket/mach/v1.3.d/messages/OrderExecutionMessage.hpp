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
#include "../bitfields/OrderExecutionFlags.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// This message format is used when a displayed order on the book executes in whole or in part.
// The execution is identified by a unique Trade ID that is unique across the exchange for the
// trading day. Subsequent partial executions of the order would be published with the same
// Order ID but different Trade ID.
class OrderExecutionMessage {
  public:
    static constexpr const char* name = "OrderExecutionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 37;
    static constexpr std::size_t fixed_size = 37;
    std::size_t encoded_size() const { return 37; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t symbol_id() const { return wire::read_u32_le(at(4)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(8)); }

    std::uint64_t trade_id() const { return wire::read_u64_le(at(16)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(24))), -6); }

    std::uint32_t size() const { return wire::read_u32_le(at(32)); }

    OrderExecutionFlags order_execution_flags() const { return OrderExecutionFlags{ bytes_.subspan(36) }; }

    void print(std::ostream& out) const {
        out << "OrderExecutionMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", symbol_id=";
        out << symbol_id();
        out << ", order_id=";
        out << order_id();
        out << ", trade_id=";
        out << trade_id();
        out << ", price=";
        out << price();
        out << ", size=";
        out << size();
        out << ", order_execution_flags=";
        order_execution_flags().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderExecutionMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
