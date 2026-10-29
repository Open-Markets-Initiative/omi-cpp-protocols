#include "OrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

OrderExecutedMessage::OrderExecutedMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint32_t executed_quantity, std::uint64_t execution_id, TradeCondition trade_condition)
  : time_offset_(time_offset), order_id_(order_id), executed_quantity_(executed_quantity), execution_id_(execution_id), trade_condition_(trade_condition) {}

std::chrono::nanoseconds OrderExecutedMessage::time_offset() const { return time_offset_; }
void OrderExecutedMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t OrderExecutedMessage::order_id() const { return order_id_; }
void OrderExecutedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t OrderExecutedMessage::executed_quantity() const { return executed_quantity_; }
void OrderExecutedMessage::set_executed_quantity(std::uint32_t value) { executed_quantity_ = value; }

std::uint64_t OrderExecutedMessage::execution_id() const { return execution_id_; }
void OrderExecutedMessage::set_execution_id(std::uint64_t value) { execution_id_ = value; }

TradeCondition OrderExecutedMessage::trade_condition() const { return trade_condition_; }
void OrderExecutedMessage::set_trade_condition(TradeCondition value) { trade_condition_ = value; }

MessageCode OrderExecutedMessage::type() const { return message_type; }

std::string_view OrderExecutedMessage::name() const { return "Order Executed Message"; }

std::size_t OrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    executed_quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    execution_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    trade_condition_ = static_cast<TradeCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(executed_quantity_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(execution_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(trade_condition_));
    offset += 1;

    return offset;
}

std::size_t OrderExecutedMessage::encoded_size() const {
    return wire_size;
}

void OrderExecutedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderExecutedMessage::clone() const {
    return std::make_unique<OrderExecutedMessage>(*this);
}

void OrderExecutedMessage::print(std::ostream& out) const {
    out << "OrderExecutedMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", executed_quantity=";
    out << executed_quantity_;
    out << ", execution_id=";
    out << execution_id_;
    out << ", trade_condition=";
    out << trade_condition_;
    out << '}';
}

bool OrderExecutedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedMessage::operator==(const OrderExecutedMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && executed_quantity_ == other.executed_quantity_
        && execution_id_ == other.execution_id_
        && trade_condition_ == other.trade_condition_;
}

bool OrderExecutedMessage::operator!=(const OrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
