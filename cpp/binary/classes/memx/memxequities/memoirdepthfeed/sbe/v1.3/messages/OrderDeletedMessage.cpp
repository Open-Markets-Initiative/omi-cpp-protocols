#include "OrderDeletedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

OrderDeletedMessage::OrderDeletedMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, std::uint64_t order_id)
  : timestamp_(timestamp), security_id_(security_id), order_id_(order_id) {}

std::chrono::nanoseconds OrderDeletedMessage::timestamp() const { return timestamp_; }
void OrderDeletedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t OrderDeletedMessage::security_id() const { return security_id_; }
void OrderDeletedMessage::set_security_id(std::uint16_t value) { security_id_ = value; }

std::uint64_t OrderDeletedMessage::order_id() const { return order_id_; }
void OrderDeletedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

PayloadCode OrderDeletedMessage::type() const { return message_type; }

std::string_view OrderDeletedMessage::name() const { return "Order Deleted Message"; }

std::size_t OrderDeletedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderDeletedMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    security_id_ = wire::read_u16_be(data + offset);
    offset += 2;

    order_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t OrderDeletedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderDeletedMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(security_id_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    return offset;
}

std::size_t OrderDeletedMessage::encoded_size() const {
    return wire_size;
}

void OrderDeletedMessage::accept(PayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Payload> OrderDeletedMessage::clone() const {
    return std::make_unique<OrderDeletedMessage>(*this);
}

void OrderDeletedMessage::print(std::ostream& out) const {
    out << "OrderDeletedMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", security_id=";
    out << security_id_;
    out << ", order_id=";
    out << order_id_;
    out << '}';
}

bool OrderDeletedMessage::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const OrderDeletedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderDeletedMessage::operator==(const OrderDeletedMessage& other) const {
    return timestamp_ == other.timestamp_
        && security_id_ == other.security_id_
        && order_id_ == other.order_id_;
}

bool OrderDeletedMessage::operator!=(const OrderDeletedMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
