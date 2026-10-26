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

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

// This message is sent whenever an order on the book has been cancel-replaced
class OrderReplaceMessage {
  public:
    static constexpr const char* name = "OrderReplaceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderReplaceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderReplaceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 34;
    static constexpr std::size_t fixed_size = 34;
    std::size_t encoded_size() const { return 34; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint64_t original_order_reference_number() const { return wire::read_u64_be(at(10)); }

    std::uint64_t new_order_reference_number() const { return wire::read_u64_be(at(18)); }

    std::uint32_t shares() const { return wire::read_u32_be(at(26)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(30))), -4); }

    void print(std::ostream& out) const {
        out << "OrderReplaceMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", original_order_reference_number=";
        out << original_order_reference_number();
        out << ", new_order_reference_number=";
        out << new_order_reference_number();
        out << ", shares=";
        out << shares();
        out << ", price=";
        out << price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderReplaceMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
