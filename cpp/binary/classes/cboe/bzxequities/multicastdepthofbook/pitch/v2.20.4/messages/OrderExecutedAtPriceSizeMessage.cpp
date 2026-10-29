#include "OrderExecutedAtPriceSizeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

OrderExecutedAtPriceSizeMessage::OrderExecutedAtPriceSizeMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint32_t executed_quantity, std::uint32_t remaining_quantity, std::uint64_t execution_id, Decimal price_binary_long_price_8)
  : time_offset_(time_offset), order_id_(order_id), executed_quantity_(executed_quantity), remaining_quantity_(remaining_quantity), execution_id_(execution_id), price_binary_long_price_8_(price_binary_long_price_8) {}

std::chrono::nanoseconds OrderExecutedAtPriceSizeMessage::time_offset() const { return time_offset_; }
void OrderExecutedAtPriceSizeMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t OrderExecutedAtPriceSizeMessage::order_id() const { return order_id_; }
void OrderExecutedAtPriceSizeMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t OrderExecutedAtPriceSizeMessage::executed_quantity() const { return executed_quantity_; }
void OrderExecutedAtPriceSizeMessage::set_executed_quantity(std::uint32_t value) { executed_quantity_ = value; }

std::uint32_t OrderExecutedAtPriceSizeMessage::remaining_quantity() const { return remaining_quantity_; }
void OrderExecutedAtPriceSizeMessage::set_remaining_quantity(std::uint32_t value) { remaining_quantity_ = value; }

std::uint64_t OrderExecutedAtPriceSizeMessage::execution_id() const { return execution_id_; }
void OrderExecutedAtPriceSizeMessage::set_execution_id(std::uint64_t value) { execution_id_ = value; }

Decimal OrderExecutedAtPriceSizeMessage::price_binary_long_price_8() const { return price_binary_long_price_8_; }
void OrderExecutedAtPriceSizeMessage::set_price_binary_long_price_8(Decimal value) { price_binary_long_price_8_ = value; }

MessageCode OrderExecutedAtPriceSizeMessage::type() const { return message_type; }

std::string_view OrderExecutedAtPriceSizeMessage::name() const { return "Order Executed At Price Size Message"; }

std::size_t OrderExecutedAtPriceSizeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedAtPriceSizeMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    executed_quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    remaining_quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    execution_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_binary_long_price_8_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t OrderExecutedAtPriceSizeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedAtPriceSizeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(executed_quantity_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(remaining_quantity_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(execution_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_binary_long_price_8_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t OrderExecutedAtPriceSizeMessage::encoded_size() const {
    return wire_size;
}

void OrderExecutedAtPriceSizeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderExecutedAtPriceSizeMessage::clone() const {
    return std::make_unique<OrderExecutedAtPriceSizeMessage>(*this);
}

void OrderExecutedAtPriceSizeMessage::print(std::ostream& out) const {
    out << "OrderExecutedAtPriceSizeMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", executed_quantity=";
    out << executed_quantity_;
    out << ", remaining_quantity=";
    out << remaining_quantity_;
    out << ", execution_id=";
    out << execution_id_;
    out << ", price_binary_long_price_8=";
    out << price_binary_long_price_8_;
    out << '}';
}

bool OrderExecutedAtPriceSizeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutedAtPriceSizeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedAtPriceSizeMessage::operator==(const OrderExecutedAtPriceSizeMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && executed_quantity_ == other.executed_quantity_
        && remaining_quantity_ == other.remaining_quantity_
        && execution_id_ == other.execution_id_
        && price_binary_long_price_8_ == other.price_binary_long_price_8_;
}

bool OrderExecutedAtPriceSizeMessage::operator!=(const OrderExecutedAtPriceSizeMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
