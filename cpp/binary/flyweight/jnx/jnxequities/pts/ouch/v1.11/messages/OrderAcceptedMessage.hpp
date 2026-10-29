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
#include "../enums/Capacity.hpp"
#include "../enums/OrderState.hpp"
#include "../enums/OrderClassification.hpp"
#include "../enums/CashMarginType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// An Order Accepted Message acknowledges the receipt and acceptance of a valid Enter Order
// Message
class OrderAcceptedMessage {
  public:
    static constexpr const char* name = "OrderAcceptedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderAcceptedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderAcceptedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 64;
    static constexpr std::size_t fixed_size = 64;
    std::size_t encoded_size() const { return 64; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t order_token() const { return wire::read_u32_be(at(8)); }

    std::string_view client_reference() const { return view::text(at(12), 10, ' '); }

    BuySellIndicator buy_sell_indicator() const { return static_cast<BuySellIndicator>(wire::read_char(at(22))); }

    std::uint32_t quantity() const { return wire::read_u32_be(at(23)); }

    std::uint32_t orderbook_id() const { return wire::read_u32_be(at(27)); }

    std::string_view group() const { return view::text(at(31), 4, ' '); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(35))), -1); }

    TimeInForce time_in_force() const { return static_cast<TimeInForce>(wire::read_u32_be(at(39))); }

    std::uint32_t firm_id() const { return wire::read_u32_be(at(43)); }

    Display display() const { return static_cast<Display>(wire::read_char(at(47))); }

    Capacity capacity() const { return static_cast<Capacity>(wire::read_char(at(48))); }

    std::uint64_t order_number() const { return wire::read_u64_be(at(49)); }

    std::uint32_t minimum_quantity() const { return wire::read_u32_be(at(57)); }

    OrderState order_state() const { return static_cast<OrderState>(wire::read_char(at(61))); }

    OrderClassification order_classification() const { return static_cast<OrderClassification>(wire::read_char(at(62))); }

    CashMarginType cash_margin_type() const { return static_cast<CashMarginType>(wire::read_char(at(63))); }

    void print(std::ostream& out) const {
        out << "OrderAcceptedMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "Asia/Tokyo");
        out << ", order_token=";
        out << order_token();
        out << ", client_reference=";
        print::text(out, client_reference());
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
        out << ", firm_id=";
        out << firm_id();
        out << ", display=";
        out << display();
        out << ", capacity=";
        out << capacity();
        out << ", order_number=";
        out << order_number();
        out << ", minimum_quantity=";
        out << minimum_quantity();
        out << ", order_state=";
        out << order_state();
        out << ", order_classification=";
        out << order_classification();
        out << ", cash_margin_type=";
        out << cash_margin_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderAcceptedMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
