#include "OrderReducedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

OrderReducedMessage::OrderReducedMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, std::uint64_t order_id, std::uint32_t quantity)
  : timestamp_(timestamp), security_id_(security_id), order_id_(order_id), quantity_(quantity) {}

std::chrono::nanoseconds OrderReducedMessage::timestamp() const { return timestamp_; }
void OrderReducedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t OrderReducedMessage::security_id() const { return security_id_; }
void OrderReducedMessage::set_security_id(std::uint16_t value) { security_id_ = value; }

std::uint64_t OrderReducedMessage::order_id() const { return order_id_; }
void OrderReducedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t OrderReducedMessage::quantity() const { return quantity_; }
void OrderReducedMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

PayloadCode OrderReducedMessage::type() const { return message_type; }

std::string_view OrderReducedMessage::name() const { return "Order Reduced Message"; }

std::size_t OrderReducedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderReducedMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    security_id_ = wire::read_u16_be(data + offset);
    offset += 2;

    order_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t OrderReducedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderReducedMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(security_id_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    return offset;
}

std::size_t OrderReducedMessage::encoded_size() const {
    return wire_size;
}

void OrderReducedMessage::accept(PayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Payload> OrderReducedMessage::clone() const {
    return std::make_unique<OrderReducedMessage>(*this);
}

void OrderReducedMessage::print(std::ostream& out) const {
    out << "OrderReducedMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", security_id=";
    out << security_id_;
    out << ", order_id=";
    out << order_id_;
    out << ", quantity=";
    out << quantity_;
    out << '}';
}

bool OrderReducedMessage::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const OrderReducedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderReducedMessage::operator==(const OrderReducedMessage& other) const {
    return timestamp_ == other.timestamp_
        && security_id_ == other.security_id_
        && order_id_ == other.order_id_
        && quantity_ == other.quantity_;
}

bool OrderReducedMessage::operator!=(const OrderReducedMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
