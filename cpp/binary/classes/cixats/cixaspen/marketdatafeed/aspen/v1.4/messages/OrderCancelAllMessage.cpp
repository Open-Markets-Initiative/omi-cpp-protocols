#include "OrderCancelAllMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

OrderCancelAllMessage::OrderCancelAllMessage(std::chrono::nanoseconds timestamp, std::uint64_t order_id)
  : timestamp_(timestamp), order_id_(order_id) {}

std::chrono::nanoseconds OrderCancelAllMessage::timestamp() const { return timestamp_; }
void OrderCancelAllMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t OrderCancelAllMessage::order_id() const { return order_id_; }
void OrderCancelAllMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

MessageCode OrderCancelAllMessage::type() const { return message_type; }

std::string_view OrderCancelAllMessage::name() const { return "Order Cancel All Message"; }

std::size_t OrderCancelAllMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderCancelAllMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t OrderCancelAllMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderCancelAllMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    return offset;
}

std::size_t OrderCancelAllMessage::encoded_size() const {
    return wire_size;
}

void OrderCancelAllMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderCancelAllMessage::clone() const {
    return std::make_unique<OrderCancelAllMessage>(*this);
}

void OrderCancelAllMessage::print(std::ostream& out) const {
    out << "OrderCancelAllMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", order_id=";
    out << order_id_;
    out << '}';
}

bool OrderCancelAllMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderCancelAllMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderCancelAllMessage::operator==(const OrderCancelAllMessage& other) const {
    return timestamp_ == other.timestamp_
        && order_id_ == other.order_id_;
}

bool OrderCancelAllMessage::operator!=(const OrderCancelAllMessage& other) const {
    return !(*this == other);
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
