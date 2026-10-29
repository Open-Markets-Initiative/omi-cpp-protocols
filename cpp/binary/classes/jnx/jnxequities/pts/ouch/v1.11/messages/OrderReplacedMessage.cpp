#include "OrderReplacedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

OrderReplacedMessage::OrderReplacedMessage(std::chrono::nanoseconds timestamp, std::uint32_t replacement_order_token, BuySellIndicator buy_sell_indicator, std::uint32_t quantity, std::uint32_t orderbook_id, const std::string& group, Decimal price, TimeInForce time_in_force, Display display, std::uint64_t order_number, std::uint32_t minimum_quantity, OrderState order_state, std::uint32_t previous_order_token)
  : timestamp_(timestamp), replacement_order_token_(replacement_order_token), buy_sell_indicator_(buy_sell_indicator), quantity_(quantity), orderbook_id_(orderbook_id), group_(group), price_(price), time_in_force_(time_in_force), display_(display), order_number_(order_number), minimum_quantity_(minimum_quantity), order_state_(order_state), previous_order_token_(previous_order_token) {}

std::chrono::nanoseconds OrderReplacedMessage::timestamp() const { return timestamp_; }
void OrderReplacedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t OrderReplacedMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t OrderReplacedMessage::replacement_order_token() const { return replacement_order_token_; }
void OrderReplacedMessage::set_replacement_order_token(std::uint32_t value) { replacement_order_token_ = value; }

BuySellIndicator OrderReplacedMessage::buy_sell_indicator() const { return buy_sell_indicator_; }
void OrderReplacedMessage::set_buy_sell_indicator(BuySellIndicator value) { buy_sell_indicator_ = value; }

std::uint32_t OrderReplacedMessage::quantity() const { return quantity_; }
void OrderReplacedMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

std::uint32_t OrderReplacedMessage::orderbook_id() const { return orderbook_id_; }
void OrderReplacedMessage::set_orderbook_id(std::uint32_t value) { orderbook_id_ = value; }

const std::string& OrderReplacedMessage::group() const { return group_; }
std::string& OrderReplacedMessage::group() { return group_; }
void OrderReplacedMessage::set_group(const std::string& value) { group_ = value; }

Decimal OrderReplacedMessage::price() const { return price_; }
void OrderReplacedMessage::set_price(Decimal value) { price_ = value; }

TimeInForce OrderReplacedMessage::time_in_force() const { return time_in_force_; }
void OrderReplacedMessage::set_time_in_force(TimeInForce value) { time_in_force_ = value; }

Display OrderReplacedMessage::display() const { return display_; }
void OrderReplacedMessage::set_display(Display value) { display_ = value; }

std::uint64_t OrderReplacedMessage::order_number() const { return order_number_; }
void OrderReplacedMessage::set_order_number(std::uint64_t value) { order_number_ = value; }

std::uint32_t OrderReplacedMessage::minimum_quantity() const { return minimum_quantity_; }
void OrderReplacedMessage::set_minimum_quantity(std::uint32_t value) { minimum_quantity_ = value; }

OrderState OrderReplacedMessage::order_state() const { return order_state_; }
void OrderReplacedMessage::set_order_state(OrderState value) { order_state_ = value; }

std::uint32_t OrderReplacedMessage::previous_order_token() const { return previous_order_token_; }
void OrderReplacedMessage::set_previous_order_token(std::uint32_t value) { previous_order_token_ = value; }

SequencedMessageCode OrderReplacedMessage::type() const { return message_type; }

std::string_view OrderReplacedMessage::name() const { return "Order Replaced Message"; }

std::size_t OrderReplacedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderReplacedMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    replacement_order_token_ = wire::read_u32_be(data + offset);
    offset += 4;

    buy_sell_indicator_ = static_cast<BuySellIndicator>(wire::read_char(data + offset));
    offset += 1;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    orderbook_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    group_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -1);
    offset += 4;

    time_in_force_ = static_cast<TimeInForce>(wire::read_u32_be(data + offset));
    offset += 4;

    display_ = static_cast<Display>(wire::read_char(data + offset));
    offset += 1;

    order_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    minimum_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    order_state_ = static_cast<OrderState>(wire::read_char(data + offset));
    offset += 1;

    previous_order_token_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t OrderReplacedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderReplacedMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(replacement_order_token_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(buy_sell_indicator_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(orderbook_id_));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', group_);
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(time_in_force_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(display_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(minimum_quantity_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(order_state_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(previous_order_token_));
    offset += 4;

    return offset;
}

std::size_t OrderReplacedMessage::encoded_size() const {
    return wire_size;
}

void OrderReplacedMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> OrderReplacedMessage::clone() const {
    return std::make_unique<OrderReplacedMessage>(*this);
}

void OrderReplacedMessage::print(std::ostream& out) const {
    out << "OrderReplacedMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "Asia/Tokyo");
    out << ", replacement_order_token=";
    out << replacement_order_token_;
    out << ", buy_sell_indicator=";
    out << buy_sell_indicator_;
    out << ", quantity=";
    out << quantity_;
    out << ", orderbook_id=";
    out << orderbook_id_;
    out << ", group=";
    print::text(out, group_);
    out << ", price=";
    out << price_;
    out << ", time_in_force=";
    out << time_in_force_;
    out << ", display=";
    out << display_;
    out << ", order_number=";
    out << order_number_;
    out << ", minimum_quantity=";
    out << minimum_quantity_;
    out << ", order_state=";
    out << order_state_;
    out << ", previous_order_token=";
    out << previous_order_token_;
    out << '}';
}

bool OrderReplacedMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const OrderReplacedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderReplacedMessage::operator==(const OrderReplacedMessage& other) const {
    return timestamp_ == other.timestamp_
        && replacement_order_token_ == other.replacement_order_token_
        && buy_sell_indicator_ == other.buy_sell_indicator_
        && quantity_ == other.quantity_
        && orderbook_id_ == other.orderbook_id_
        && group_ == other.group_
        && price_ == other.price_
        && time_in_force_ == other.time_in_force_
        && display_ == other.display_
        && order_number_ == other.order_number_
        && minimum_quantity_ == other.minimum_quantity_
        && order_state_ == other.order_state_
        && previous_order_token_ == other.previous_order_token_;
}

bool OrderReplacedMessage::operator!=(const OrderReplacedMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
