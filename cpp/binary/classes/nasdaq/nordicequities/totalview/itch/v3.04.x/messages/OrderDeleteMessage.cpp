#include "OrderDeleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

OrderDeleteMessage::OrderDeleteMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t order_reference_number)
  : timestamp_(timestamp), tracking_number_(tracking_number), order_reference_number_(order_reference_number) {}

std::chrono::nanoseconds OrderDeleteMessage::timestamp() const { return timestamp_; }
void OrderDeleteMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t OrderDeleteMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "UTC").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint16_t OrderDeleteMessage::tracking_number() const { return tracking_number_; }
void OrderDeleteMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::uint64_t OrderDeleteMessage::order_reference_number() const { return order_reference_number_; }
void OrderDeleteMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

MessageCode OrderDeleteMessage::type() const { return message_type; }

std::string_view OrderDeleteMessage::name() const { return "Order Delete Message"; }

std::size_t OrderDeleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderDeleteMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t OrderDeleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderDeleteMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    return offset;
}

std::size_t OrderDeleteMessage::encoded_size() const {
    return wire_size;
}

void OrderDeleteMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderDeleteMessage::clone() const {
    return std::make_unique<OrderDeleteMessage>(*this);
}

void OrderDeleteMessage::print(std::ostream& out) const {
    out << "OrderDeleteMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "UTC");
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << '}';
}

bool OrderDeleteMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderDeleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderDeleteMessage::operator==(const OrderDeleteMessage& other) const {
    return timestamp_ == other.timestamp_
        && tracking_number_ == other.tracking_number_
        && order_reference_number_ == other.order_reference_number_;
}

bool OrderDeleteMessage::operator!=(const OrderDeleteMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
