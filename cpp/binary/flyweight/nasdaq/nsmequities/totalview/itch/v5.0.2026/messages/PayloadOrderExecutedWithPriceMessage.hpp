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
#include "../enums/Printable.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

// This message is sent whenever an order on the book is executed in whole or in part at a
// price different from the initial display price
class PayloadOrderExecutedWithPriceMessage {
  public:
    static constexpr const char* name = "PayloadOrderExecutedWithPriceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadOrderExecutedWithPriceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadOrderExecutedWithPriceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 35;
    static constexpr std::size_t fixed_size = 35;
    std::size_t encoded_size() const { return 35; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint64_t order_reference_number() const { return wire::read_u64_be(at(10)); }

    std::uint32_t executed_shares() const { return wire::read_u32_be(at(18)); }

    std::uint64_t match_number() const { return wire::read_u64_be(at(22)); }

    Printable printable() const { return static_cast<Printable>(wire::read_char(at(30))); }

    Decimal execution_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(31))), -4); }

    void print(std::ostream& out) const {
        out << "PayloadOrderExecutedWithPriceMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", order_reference_number=";
        out << order_reference_number();
        out << ", executed_shares=";
        out << executed_shares();
        out << ", match_number=";
        out << match_number();
        out << ", printable=";
        out << printable();
        out << ", execution_price=";
        out << execution_price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadOrderExecutedWithPriceMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
