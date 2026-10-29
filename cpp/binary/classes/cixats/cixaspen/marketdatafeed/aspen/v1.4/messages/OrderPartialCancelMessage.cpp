#include "OrderPartialCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

OrderPartialCancelMessage::OrderPartialCancelMessage(std::chrono::nanoseconds timestamp, std::uint64_t order_id, Decimal quantity_canceled)
  : timestamp_(timestamp), order_id_(order_id), quantity_canceled_(quantity_canceled) {}

std::chrono::nanoseconds OrderPartialCancelMessage::timestamp() const { return timestamp_; }
void OrderPartialCancelMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t OrderPartialCancelMessage::order_id() const { return order_id_; }
void OrderPartialCancelMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

Decimal OrderPartialCancelMessage::quantity_canceled() const { return quantity_canceled_; }
void OrderPartialCancelMessage::set_quantity_canceled(Decimal value) { quantity_canceled_ = value; }

MessageCode OrderPartialCancelMessage::type() const { return message_type; }

std::string_view OrderPartialCancelMessage::name() const { return "Order Partial Cancel Message"; }

std::size_t OrderPartialCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderPartialCancelMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    quantity_canceled_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t OrderPartialCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderPartialCancelMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(quantity_canceled_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t OrderPartialCancelMessage::encoded_size() const {
    return wire_size;
}

void OrderPartialCancelMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderPartialCancelMessage::clone() const {
    return std::make_unique<OrderPartialCancelMessage>(*this);
}

void OrderPartialCancelMessage::print(std::ostream& out) const {
    out << "OrderPartialCancelMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", quantity_canceled=";
    out << quantity_canceled_;
    out << '}';
}

bool OrderPartialCancelMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderPartialCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderPartialCancelMessage::operator==(const OrderPartialCancelMessage& other) const {
    return timestamp_ == other.timestamp_
        && order_id_ == other.order_id_
        && quantity_canceled_ == other.quantity_canceled_;
}

bool OrderPartialCancelMessage::operator!=(const OrderPartialCancelMessage& other) const {
    return !(*this == other);
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
