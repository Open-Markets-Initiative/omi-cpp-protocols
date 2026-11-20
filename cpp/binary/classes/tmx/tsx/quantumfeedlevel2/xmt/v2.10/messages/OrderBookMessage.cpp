// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/OrderBookMessage.cpp
#include "OrderBookMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

OrderBookMessage::OrderBookMessage(const std::string& symbol, std::optional<std::uint16_t> broker_number, OrderSide order_side, std::optional<std::uint64_t> order_id, std::optional<Decimal> price, std::optional<std::uint32_t> volume, std::optional<std::chrono::microseconds> priority_time_stamp)
  : symbol_(symbol), broker_number_(broker_number), order_side_(order_side), order_id_(order_id), price_(price), volume_(volume), priority_time_stamp_(priority_time_stamp) {}

const std::string& OrderBookMessage::symbol() const { return symbol_; }
std::string& OrderBookMessage::symbol() { return symbol_; }
void OrderBookMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::optional<std::uint16_t> OrderBookMessage::broker_number() const { return broker_number_; }
void OrderBookMessage::set_broker_number(std::optional<std::uint16_t> value) { broker_number_ = value; }

OrderSide OrderBookMessage::order_side() const { return order_side_; }
void OrderBookMessage::set_order_side(OrderSide value) { order_side_ = value; }

std::optional<std::uint64_t> OrderBookMessage::order_id() const { return order_id_; }
void OrderBookMessage::set_order_id(std::optional<std::uint64_t> value) { order_id_ = value; }

std::optional<Decimal> OrderBookMessage::price() const { return price_; }
void OrderBookMessage::set_price(std::optional<Decimal> value) { price_ = value; }

std::optional<std::uint32_t> OrderBookMessage::volume() const { return volume_; }
void OrderBookMessage::set_volume(std::optional<std::uint32_t> value) { volume_ = value; }

std::optional<std::chrono::microseconds> OrderBookMessage::priority_time_stamp() const { return priority_time_stamp_; }
void OrderBookMessage::set_priority_time_stamp(std::optional<std::chrono::microseconds> value) { priority_time_stamp_ = value; }

MessageCode OrderBookMessage::type() const { return message_type; }

std::string_view OrderBookMessage::name() const { return "Order Book Message"; }

std::size_t OrderBookMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderBookMessage", wire_size, length);

    symbol_ = wire::read_text(data + offset, 9, ' ');
    offset += 9;

    broker_number_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    order_side_ = static_cast<OrderSide>(wire::read_char(data + offset));
    offset += 1;

    order_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    price_ = wire::nullable_decimal(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL), -6);
    offset += 8;

    volume_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    priority_time_stamp_ = wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t OrderBookMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderBookMessage", wire_size, capacity);

    wire::write_text(data + offset, 9, ' ', symbol_);
    offset += 9;

    wire::write_u16_le(data + offset, broker_number_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(order_side_));
    offset += 1;

    wire::write_u64_le(data + offset, order_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, price_ ? static_cast<std::uint64_t>(price_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, volume_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, priority_time_stamp_ ? static_cast<std::uint64_t>(priority_time_stamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t OrderBookMessage::encoded_size() const {
    return wire_size;
}

void OrderBookMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderBookMessage::clone() const {
    return std::make_unique<OrderBookMessage>(*this);
}

void OrderBookMessage::print(std::ostream& out) const {
    out << "OrderBookMessage{";
    out << "symbol=";
    print::text(out, symbol_);
    out << ", broker_number=";
    print::optional(out, broker_number_);
    out << ", order_side=";
    out << order_side_;
    out << ", order_id=";
    print::optional(out, order_id_);
    out << ", price=";
    print::optional(out, price_);
    out << ", volume=";
    print::optional(out, volume_);
    out << ", priority_time_stamp=";
    print::optional_duration(out, priority_time_stamp_);
    out << '}';
}

bool OrderBookMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderBookMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderBookMessage::operator==(const OrderBookMessage& other) const {
    return symbol_ == other.symbol_
        && broker_number_ == other.broker_number_
        && order_side_ == other.order_side_
        && order_id_ == other.order_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && priority_time_stamp_ == other.priority_time_stamp_;
}

bool OrderBookMessage::operator!=(const OrderBookMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
