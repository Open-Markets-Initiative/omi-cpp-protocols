#include "OrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

OrderExecutedMessage::OrderExecutedMessage(std::uint32_t nanosecond, std::uint64_t order_id, std::uint32_t executed_quantity, std::uint64_t trade_match_id)
  : nanosecond_(nanosecond), order_id_(order_id), executed_quantity_(executed_quantity), trade_match_id_(trade_match_id) {}

std::uint32_t OrderExecutedMessage::nanosecond() const { return nanosecond_; }
void OrderExecutedMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint64_t OrderExecutedMessage::order_id() const { return order_id_; }
void OrderExecutedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t OrderExecutedMessage::executed_quantity() const { return executed_quantity_; }
void OrderExecutedMessage::set_executed_quantity(std::uint32_t value) { executed_quantity_ = value; }

std::uint64_t OrderExecutedMessage::trade_match_id() const { return trade_match_id_; }
void OrderExecutedMessage::set_trade_match_id(std::uint64_t value) { trade_match_id_ = value; }

MessageCode OrderExecutedMessage::type() const { return message_type; }

std::string_view OrderExecutedMessage::name() const { return "Order Executed Message"; }

std::size_t OrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedMessage", wire_size, length);

    nanosecond_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    executed_quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_match_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t OrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanosecond_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(executed_quantity_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(trade_match_id_));
    offset += 8;

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
    out << "nanosecond=";
    out << nanosecond_;
    out << ", order_id=";
    out << order_id_;
    out << ", executed_quantity=";
    out << executed_quantity_;
    out << ", trade_match_id=";
    out << trade_match_id_;
    out << '}';
}

bool OrderExecutedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedMessage::operator==(const OrderExecutedMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && order_id_ == other.order_id_
        && executed_quantity_ == other.executed_quantity_
        && trade_match_id_ == other.trade_match_id_;
}

bool OrderExecutedMessage::operator!=(const OrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
