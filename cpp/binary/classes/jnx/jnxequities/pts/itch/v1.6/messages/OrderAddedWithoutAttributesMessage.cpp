#include "OrderAddedWithoutAttributesMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

OrderAddedWithoutAttributesMessage::OrderAddedWithoutAttributesMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_number, BuySellIndicator buy_sell_indicator, std::uint32_t quantity, std::uint32_t orderbook_id, const std::string& group, Decimal price)
  : nanoseconds_(nanoseconds), order_number_(order_number), buy_sell_indicator_(buy_sell_indicator), quantity_(quantity), orderbook_id_(orderbook_id), group_(group), price_(price) {}

std::chrono::nanoseconds OrderAddedWithoutAttributesMessage::nanoseconds() const { return nanoseconds_; }
void OrderAddedWithoutAttributesMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t OrderAddedWithoutAttributesMessage::order_number() const { return order_number_; }
void OrderAddedWithoutAttributesMessage::set_order_number(std::uint64_t value) { order_number_ = value; }

BuySellIndicator OrderAddedWithoutAttributesMessage::buy_sell_indicator() const { return buy_sell_indicator_; }
void OrderAddedWithoutAttributesMessage::set_buy_sell_indicator(BuySellIndicator value) { buy_sell_indicator_ = value; }

std::uint32_t OrderAddedWithoutAttributesMessage::quantity() const { return quantity_; }
void OrderAddedWithoutAttributesMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

std::uint32_t OrderAddedWithoutAttributesMessage::orderbook_id() const { return orderbook_id_; }
void OrderAddedWithoutAttributesMessage::set_orderbook_id(std::uint32_t value) { orderbook_id_ = value; }

const std::string& OrderAddedWithoutAttributesMessage::group() const { return group_; }
std::string& OrderAddedWithoutAttributesMessage::group() { return group_; }
void OrderAddedWithoutAttributesMessage::set_group(const std::string& value) { group_ = value; }

Decimal OrderAddedWithoutAttributesMessage::price() const { return price_; }
void OrderAddedWithoutAttributesMessage::set_price(Decimal value) { price_ = value; }

MessageCode OrderAddedWithoutAttributesMessage::type() const { return message_type; }

std::string_view OrderAddedWithoutAttributesMessage::name() const { return "Order Added Without Attributes Message"; }

std::size_t OrderAddedWithoutAttributesMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderAddedWithoutAttributesMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_number_ = wire::read_u64_be(data + offset);
    offset += 8;

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

    return offset;
}

std::size_t OrderAddedWithoutAttributesMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderAddedWithoutAttributesMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_number_));
    offset += 8;

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

    return offset;
}

std::size_t OrderAddedWithoutAttributesMessage::encoded_size() const {
    return wire_size;
}

void OrderAddedWithoutAttributesMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderAddedWithoutAttributesMessage::clone() const {
    return std::make_unique<OrderAddedWithoutAttributesMessage>(*this);
}

void OrderAddedWithoutAttributesMessage::print(std::ostream& out) const {
    out << "OrderAddedWithoutAttributesMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_number=";
    out << order_number_;
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
    out << '}';
}

bool OrderAddedWithoutAttributesMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderAddedWithoutAttributesMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderAddedWithoutAttributesMessage::operator==(const OrderAddedWithoutAttributesMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_number_ == other.order_number_
        && buy_sell_indicator_ == other.buy_sell_indicator_
        && quantity_ == other.quantity_
        && orderbook_id_ == other.orderbook_id_
        && group_ == other.group_
        && price_ == other.price_;
}

bool OrderAddedWithoutAttributesMessage::operator!=(const OrderAddedWithoutAttributesMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_6
