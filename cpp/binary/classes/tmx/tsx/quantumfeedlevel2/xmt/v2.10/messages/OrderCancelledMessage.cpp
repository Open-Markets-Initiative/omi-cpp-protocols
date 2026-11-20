// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/OrderCancelledMessage.cpp
#include "OrderCancelledMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

OrderCancelledMessage::OrderCancelledMessage(const std::string& symbol, std::optional<std::uint16_t> broker_number, OrderSide order_side, std::optional<std::uint64_t> order_id, std::optional<std::chrono::microseconds> trading_system_time_stamp)
  : symbol_(symbol), broker_number_(broker_number), order_side_(order_side), order_id_(order_id), trading_system_time_stamp_(trading_system_time_stamp) {}

const std::string& OrderCancelledMessage::symbol() const { return symbol_; }
std::string& OrderCancelledMessage::symbol() { return symbol_; }
void OrderCancelledMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::optional<std::uint16_t> OrderCancelledMessage::broker_number() const { return broker_number_; }
void OrderCancelledMessage::set_broker_number(std::optional<std::uint16_t> value) { broker_number_ = value; }

OrderSide OrderCancelledMessage::order_side() const { return order_side_; }
void OrderCancelledMessage::set_order_side(OrderSide value) { order_side_ = value; }

std::optional<std::uint64_t> OrderCancelledMessage::order_id() const { return order_id_; }
void OrderCancelledMessage::set_order_id(std::optional<std::uint64_t> value) { order_id_ = value; }

std::optional<std::chrono::microseconds> OrderCancelledMessage::trading_system_time_stamp() const { return trading_system_time_stamp_; }
void OrderCancelledMessage::set_trading_system_time_stamp(std::optional<std::chrono::microseconds> value) { trading_system_time_stamp_ = value; }

MessageCode OrderCancelledMessage::type() const { return message_type; }

std::string_view OrderCancelledMessage::name() const { return "Order Cancelled Message"; }

std::size_t OrderCancelledMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderCancelledMessage", wire_size, length);

    symbol_ = wire::read_text(data + offset, 9, ' ');
    offset += 9;

    broker_number_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    order_side_ = static_cast<OrderSide>(wire::read_char(data + offset));
    offset += 1;

    order_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    trading_system_time_stamp_ = wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t OrderCancelledMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderCancelledMessage", wire_size, capacity);

    wire::write_text(data + offset, 9, ' ', symbol_);
    offset += 9;

    wire::write_u16_le(data + offset, broker_number_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(order_side_));
    offset += 1;

    wire::write_u64_le(data + offset, order_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, trading_system_time_stamp_ ? static_cast<std::uint64_t>(trading_system_time_stamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t OrderCancelledMessage::encoded_size() const {
    return wire_size;
}

void OrderCancelledMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderCancelledMessage::clone() const {
    return std::make_unique<OrderCancelledMessage>(*this);
}

void OrderCancelledMessage::print(std::ostream& out) const {
    out << "OrderCancelledMessage{";
    out << "symbol=";
    print::text(out, symbol_);
    out << ", broker_number=";
    print::optional(out, broker_number_);
    out << ", order_side=";
    out << order_side_;
    out << ", order_id=";
    print::optional(out, order_id_);
    out << ", trading_system_time_stamp=";
    print::optional_duration(out, trading_system_time_stamp_);
    out << '}';
}

bool OrderCancelledMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderCancelledMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderCancelledMessage::operator==(const OrderCancelledMessage& other) const {
    return symbol_ == other.symbol_
        && broker_number_ == other.broker_number_
        && order_side_ == other.order_side_
        && order_id_ == other.order_id_
        && trading_system_time_stamp_ == other.trading_system_time_stamp_;
}

bool OrderCancelledMessage::operator!=(const OrderCancelledMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
