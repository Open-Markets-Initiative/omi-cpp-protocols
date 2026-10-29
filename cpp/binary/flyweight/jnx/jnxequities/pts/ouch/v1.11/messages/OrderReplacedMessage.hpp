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
#include "../enums/Group.hpp"
#include "../common/Decimal.hpp"
#include "../enums/TimeInForce.hpp"
#include "../enums/Display.hpp"
#include "../enums/OrderState.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// An Order Replaced Message acknowledges the receipt and acceptance of a valid Replace Order
// Message
class OrderReplacedMessage {
  public:
    static constexpr const char* name = "OrderReplacedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderReplacedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderReplacedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 51;
    static constexpr std::size_t fixed_size = 51;
    std::size_t encoded_size() const { return 51; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t replacement_order_token() const { return wire::read_u32_be(at(8)); }

    BuySellIndicator buy_sell_indicator() const { return static_cast<BuySellIndicator>(wire::read_char(at(12))); }

    std::uint32_t quantity() const { return wire::read_u32_be(at(13)); }

    std::uint32_t orderbook_id() const { return wire::read_u32_be(at(17)); }

    std::string_view group() const { return view::text(at(21), 4, ' '); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(25))), -1); }

    TimeInForce time_in_force() const { return static_cast<TimeInForce>(wire::read_u32_be(at(29))); }

    Display display() const { return static_cast<Display>(wire::read_char(at(33))); }

    std::uint64_t order_number() const { return wire::read_u64_be(at(34)); }

    std::uint32_t minimum_quantity() const { return wire::read_u32_be(at(42)); }

    OrderState order_state() const { return static_cast<OrderState>(wire::read_char(at(46))); }

    std::uint32_t previous_order_token() const { return wire::read_u32_be(at(47)); }

    void print(std::ostream& out) const {
        out << "OrderReplacedMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "Asia/Tokyo");
        out << ", replacement_order_token=";
        out << replacement_order_token();
        out << ", buy_sell_indicator=";
        out << buy_sell_indicator();
        out << ", quantity=";
        out << quantity();
        out << ", orderbook_id=";
        out << orderbook_id();
        out << ", group=";
        print::text(out, group());
        out << ", price=";
        out << price();
        out << ", time_in_force=";
        out << time_in_force();
        out << ", display=";
        out << display();
        out << ", order_number=";
        out << order_number();
        out << ", minimum_quantity=";
        out << minimum_quantity();
        out << ", order_state=";
        out << order_state();
        out << ", previous_order_token=";
        out << previous_order_token();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderReplacedMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
