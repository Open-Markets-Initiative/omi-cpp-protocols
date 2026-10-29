#include "OrderRejectedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

OrderRejectedMessage::OrderRejectedMessage(std::chrono::nanoseconds timestamp, std::uint32_t order_token, OrderRejectedReason order_rejected_reason)
  : timestamp_(timestamp), order_token_(order_token), order_rejected_reason_(order_rejected_reason) {}

std::chrono::nanoseconds OrderRejectedMessage::timestamp() const { return timestamp_; }
void OrderRejectedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t OrderRejectedMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t OrderRejectedMessage::order_token() const { return order_token_; }
void OrderRejectedMessage::set_order_token(std::uint32_t value) { order_token_ = value; }

OrderRejectedReason OrderRejectedMessage::order_rejected_reason() const { return order_rejected_reason_; }
void OrderRejectedMessage::set_order_rejected_reason(OrderRejectedReason value) { order_rejected_reason_ = value; }

SequencedMessageCode OrderRejectedMessage::type() const { return message_type; }

std::string_view OrderRejectedMessage::name() const { return "Order Rejected Message"; }

std::size_t OrderRejectedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderRejectedMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    order_token_ = wire::read_u32_be(data + offset);
    offset += 4;

    order_rejected_reason_ = static_cast<OrderRejectedReason>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OrderRejectedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderRejectedMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_token_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(order_rejected_reason_));
    offset += 1;

    return offset;
}

std::size_t OrderRejectedMessage::encoded_size() const {
    return wire_size;
}

void OrderRejectedMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> OrderRejectedMessage::clone() const {
    return std::make_unique<OrderRejectedMessage>(*this);
}

void OrderRejectedMessage::print(std::ostream& out) const {
    out << "OrderRejectedMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "Asia/Tokyo");
    out << ", order_token=";
    out << order_token_;
    out << ", order_rejected_reason=";
    out << order_rejected_reason_;
    out << '}';
}

bool OrderRejectedMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const OrderRejectedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderRejectedMessage::operator==(const OrderRejectedMessage& other) const {
    return timestamp_ == other.timestamp_
        && order_token_ == other.order_token_
        && order_rejected_reason_ == other.order_rejected_reason_;
}

bool OrderRejectedMessage::operator!=(const OrderRejectedMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
