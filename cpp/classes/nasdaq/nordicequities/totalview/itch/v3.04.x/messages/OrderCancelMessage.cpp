#include "OrderCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

OrderCancelMessage::OrderCancelMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t order_reference_number, std::uint32_t canceled_quantity)
  : timestamp_(timestamp), tracking_number_(tracking_number), order_reference_number_(order_reference_number), canceled_quantity_(canceled_quantity) {}

std::chrono::nanoseconds OrderCancelMessage::timestamp() const { return timestamp_; }
void OrderCancelMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t OrderCancelMessage::tracking_number() const { return tracking_number_; }
void OrderCancelMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::uint64_t OrderCancelMessage::order_reference_number() const { return order_reference_number_; }
void OrderCancelMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

std::uint32_t OrderCancelMessage::canceled_quantity() const { return canceled_quantity_; }
void OrderCancelMessage::set_canceled_quantity(std::uint32_t value) { canceled_quantity_ = value; }

MessageCode OrderCancelMessage::type() const { return message_type; }

std::string_view OrderCancelMessage::name() const { return "Order Cancel Message"; }

std::size_t OrderCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderCancelMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    canceled_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t OrderCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderCancelMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(canceled_quantity_));
    offset += 4;

    return offset;
}

std::size_t OrderCancelMessage::encoded_size() const {
    return wire_size;
}

void OrderCancelMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderCancelMessage::clone() const {
    return std::make_unique<OrderCancelMessage>(*this);
}

void OrderCancelMessage::print(std::ostream& out) const {
    out << "OrderCancelMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", canceled_quantity=";
    out << canceled_quantity_;
    out << '}';
}

bool OrderCancelMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderCancelMessage::operator==(const OrderCancelMessage& other) const {
    return timestamp_ == other.timestamp_
        && tracking_number_ == other.tracking_number_
        && order_reference_number_ == other.order_reference_number_
        && canceled_quantity_ == other.canceled_quantity_;
}

bool OrderCancelMessage::operator!=(const OrderCancelMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
