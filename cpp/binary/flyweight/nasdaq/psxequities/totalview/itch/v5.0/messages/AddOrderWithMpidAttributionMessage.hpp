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
#include "../enums/BuySellIndicator.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::psxequities::totalview::itch::v5_0 {

// This message will be generated for attributed orders and quotations accepted by the NASDAQ
// PSX system.
class AddOrderWithMpidAttributionMessage {
  public:
    static constexpr const char* name = "AddOrderWithMpidAttributionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderWithMpidAttributionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderWithMpidAttributionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 39;
    static constexpr std::size_t fixed_size = 39;
    std::size_t encoded_size() const { return 39; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint64_t order_reference_number() const { return wire::read_u64_be(at(10)); }

    BuySellIndicator buy_sell_indicator() const { return static_cast<BuySellIndicator>(wire::read_char(at(18))); }

    std::uint32_t shares() const { return wire::read_u32_be(at(19)); }

    std::string_view stock() const { return view::text(at(23), 8, ' '); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(31))), -4); }

    std::string_view attribution() const { return view::text(at(35), 4, ' '); }

    void print(std::ostream& out) const {
        out << "AddOrderWithMpidAttributionMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", order_reference_number=";
        out << order_reference_number();
        out << ", buy_sell_indicator=";
        out << buy_sell_indicator();
        out << ", shares=";
        out << shares();
        out << ", stock=";
        print::text(out, stock());
        out << ", price=";
        out << price();
        out << ", attribution=";
        print::text(out, attribution());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddOrderWithMpidAttributionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::psxequities::totalview::itch::v5_0
