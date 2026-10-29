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

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

// Order Executed at Price/Size messages are sent when a visible order on the Cboe book is
// executed in whole or in part at a different price than the limit price on the original Add
// Order message or the limit order price in the latest Modify Order message referencing the
// Order Id.
class OrderExecutedAtPriceSizeMessage {
  public:
    static constexpr const char* name = "OrderExecutedAtPriceSizeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutedAtPriceSizeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutedAtPriceSizeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    static constexpr std::size_t fixed_size = 36;
    std::size_t encoded_size() const { return 36; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    std::uint32_t executed_quantity() const { return wire::read_u32_le(at(12)); }

    std::uint32_t remaining_quantity() const { return wire::read_u32_le(at(16)); }

    std::uint64_t execution_id() const { return wire::read_u64_le(at(20)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(28))), -4); }

    void print(std::ostream& out) const {
        out << "OrderExecutedAtPriceSizeMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", order_id=";
        out << order_id();
        out << ", executed_quantity=";
        out << executed_quantity();
        out << ", remaining_quantity=";
        out << remaining_quantity();
        out << ", execution_id=";
        out << execution_id();
        out << ", price=";
        out << price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderExecutedAtPriceSizeMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29
