#include "OrderExecutedWithPriceSizeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

OrderExecutedWithPriceSizeMessage::OrderExecutedWithPriceSizeMessage(std::uint32_t nanosecond, std::uint64_t order_id, std::uint32_t executed_quantity, std::uint32_t display_quantity, std::uint64_t trade_match_id, Printable printable, std::int64_t price)
  : nanosecond_(nanosecond), order_id_(order_id), executed_quantity_(executed_quantity), display_quantity_(display_quantity), trade_match_id_(trade_match_id), printable_(printable), price_(price) {}

std::uint32_t OrderExecutedWithPriceSizeMessage::nanosecond() const { return nanosecond_; }
void OrderExecutedWithPriceSizeMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint64_t OrderExecutedWithPriceSizeMessage::order_id() const { return order_id_; }
void OrderExecutedWithPriceSizeMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t OrderExecutedWithPriceSizeMessage::executed_quantity() const { return executed_quantity_; }
void OrderExecutedWithPriceSizeMessage::set_executed_quantity(std::uint32_t value) { executed_quantity_ = value; }

std::uint32_t OrderExecutedWithPriceSizeMessage::display_quantity() const { return display_quantity_; }
void OrderExecutedWithPriceSizeMessage::set_display_quantity(std::uint32_t value) { display_quantity_ = value; }

std::uint64_t OrderExecutedWithPriceSizeMessage::trade_match_id() const { return trade_match_id_; }
void OrderExecutedWithPriceSizeMessage::set_trade_match_id(std::uint64_t value) { trade_match_id_ = value; }

Printable OrderExecutedWithPriceSizeMessage::printable() const { return printable_; }
void OrderExecutedWithPriceSizeMessage::set_printable(Printable value) { printable_ = value; }

std::int64_t OrderExecutedWithPriceSizeMessage::price() const { return price_; }
void OrderExecutedWithPriceSizeMessage::set_price(std::int64_t value) { price_ = value; }

MessageCode OrderExecutedWithPriceSizeMessage::type() const { return message_type; }

std::string_view OrderExecutedWithPriceSizeMessage::name() const { return "Order Executed With Price Size Message"; }

std::size_t OrderExecutedWithPriceSizeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedWithPriceSizeMessage", wire_size, length);

    nanosecond_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    executed_quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    display_quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_match_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    printable_ = static_cast<Printable>(wire::read_char(data + offset));
    offset += 1;

    price_ = wire::read_i64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t OrderExecutedWithPriceSizeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedWithPriceSizeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanosecond_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(executed_quantity_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(display_quantity_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(trade_match_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(printable_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_));
    offset += 8;

    return offset;
}

std::size_t OrderExecutedWithPriceSizeMessage::encoded_size() const {
    return wire_size;
}

void OrderExecutedWithPriceSizeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderExecutedWithPriceSizeMessage::clone() const {
    return std::make_unique<OrderExecutedWithPriceSizeMessage>(*this);
}

void OrderExecutedWithPriceSizeMessage::print(std::ostream& out) const {
    out << "OrderExecutedWithPriceSizeMessage{";
    out << "nanosecond=";
    out << nanosecond_;
    out << ", order_id=";
    out << order_id_;
    out << ", executed_quantity=";
    out << executed_quantity_;
    out << ", display_quantity=";
    out << display_quantity_;
    out << ", trade_match_id=";
    out << trade_match_id_;
    out << ", printable=";
    out << printable_;
    out << ", price=";
    out << price_;
    out << '}';
}

bool OrderExecutedWithPriceSizeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutedWithPriceSizeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedWithPriceSizeMessage::operator==(const OrderExecutedWithPriceSizeMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && order_id_ == other.order_id_
        && executed_quantity_ == other.executed_quantity_
        && display_quantity_ == other.display_quantity_
        && trade_match_id_ == other.trade_match_id_
        && printable_ == other.printable_
        && price_ == other.price_;
}

bool OrderExecutedWithPriceSizeMessage::operator!=(const OrderExecutedWithPriceSizeMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
