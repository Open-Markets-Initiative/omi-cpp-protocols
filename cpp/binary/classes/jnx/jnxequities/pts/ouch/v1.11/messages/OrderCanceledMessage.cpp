#include "OrderCanceledMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

OrderCanceledMessage::OrderCanceledMessage(std::chrono::nanoseconds timestamp, std::uint32_t order_token, std::uint32_t decrement_quantity, OrderCanceledReason order_canceled_reason)
  : timestamp_(timestamp), order_token_(order_token), decrement_quantity_(decrement_quantity), order_canceled_reason_(order_canceled_reason) {}

std::chrono::nanoseconds OrderCanceledMessage::timestamp() const { return timestamp_; }
void OrderCanceledMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t OrderCanceledMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t OrderCanceledMessage::order_token() const { return order_token_; }
void OrderCanceledMessage::set_order_token(std::uint32_t value) { order_token_ = value; }

std::uint32_t OrderCanceledMessage::decrement_quantity() const { return decrement_quantity_; }
void OrderCanceledMessage::set_decrement_quantity(std::uint32_t value) { decrement_quantity_ = value; }

OrderCanceledReason OrderCanceledMessage::order_canceled_reason() const { return order_canceled_reason_; }
void OrderCanceledMessage::set_order_canceled_reason(OrderCanceledReason value) { order_canceled_reason_ = value; }

SequencedMessageCode OrderCanceledMessage::type() const { return message_type; }

std::string_view OrderCanceledMessage::name() const { return "Order Canceled Message"; }

std::size_t OrderCanceledMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderCanceledMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    order_token_ = wire::read_u32_be(data + offset);
    offset += 4;

    decrement_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    order_canceled_reason_ = static_cast<OrderCanceledReason>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OrderCanceledMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderCanceledMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_token_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(decrement_quantity_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(order_canceled_reason_));
    offset += 1;

    return offset;
}

std::size_t OrderCanceledMessage::encoded_size() const {
    return wire_size;
}

void OrderCanceledMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> OrderCanceledMessage::clone() const {
    return std::make_unique<OrderCanceledMessage>(*this);
}

void OrderCanceledMessage::print(std::ostream& out) const {
    out << "OrderCanceledMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "Asia/Tokyo");
    out << ", order_token=";
    out << order_token_;
    out << ", decrement_quantity=";
    out << decrement_quantity_;
    out << ", order_canceled_reason=";
    out << order_canceled_reason_;
    out << '}';
}

bool OrderCanceledMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const OrderCanceledMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderCanceledMessage::operator==(const OrderCanceledMessage& other) const {
    return timestamp_ == other.timestamp_
        && order_token_ == other.order_token_
        && decrement_quantity_ == other.decrement_quantity_
        && order_canceled_reason_ == other.order_canceled_reason_;
}

bool OrderCanceledMessage::operator!=(const OrderCanceledMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
