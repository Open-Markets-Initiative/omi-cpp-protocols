#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../enums/Printable.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// An order executed at a price different to its display price
class OrderExecutedWithPriceMessage {
  public:
    static constexpr const char* name = "OrderExecutedWithPriceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutedWithPriceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutedWithPriceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 39;
    static constexpr std::size_t fixed_size = 39;
    std::size_t encoded_size() const { return 39; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "UTC").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(8)); }

    std::uint64_t order_reference_number() const { return wire::read_u64_be(at(10)); }

    std::uint32_t executed_quantity() const { return wire::read_u32_be(at(18)); }

    std::uint32_t match_number() const { return wire::read_u32_be(at(22)); }

    Printable printable() const { return static_cast<Printable>(wire::read_char(at(26))); }

    Decimal trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(27))), -4); }

    std::string_view mpid_owner() const { return view::text(at(31), 4, ' '); }

    std::string_view mpid_counterparty() const { return view::text(at(35), 4, ' '); }

    void print(std::ostream& out) const {
        out << "OrderExecutedWithPriceMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "UTC");
        out << ", tracking_number=";
        out << tracking_number();
        out << ", order_reference_number=";
        out << order_reference_number();
        out << ", executed_quantity=";
        out << executed_quantity();
        out << ", match_number=";
        out << match_number();
        out << ", printable=";
        out << printable();
        out << ", trade_price=";
        out << trade_price();
        out << ", mpid_owner=";
        print::text(out, mpid_owner());
        out << ", mpid_counterparty=";
        print::text(out, mpid_counterparty());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderExecutedWithPriceMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
