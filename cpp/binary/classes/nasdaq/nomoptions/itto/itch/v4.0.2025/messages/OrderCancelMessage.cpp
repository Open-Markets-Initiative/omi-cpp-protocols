#include "OrderCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

OrderCancelMessage::OrderCancelMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, std::uint32_t cancelled_contracts)
  : tracking_number_(tracking_number), timestamp_(timestamp), order_reference_number_(order_reference_number), cancelled_contracts_(cancelled_contracts) {}

std::uint16_t OrderCancelMessage::tracking_number() const { return tracking_number_; }
void OrderCancelMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds OrderCancelMessage::timestamp() const { return timestamp_; }
void OrderCancelMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t OrderCancelMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint64_t OrderCancelMessage::order_reference_number() const { return order_reference_number_; }
void OrderCancelMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

std::uint32_t OrderCancelMessage::cancelled_contracts() const { return cancelled_contracts_; }
void OrderCancelMessage::set_cancelled_contracts(std::uint32_t value) { cancelled_contracts_ = value; }

SequencedMessageCode OrderCancelMessage::type() const { return message_type; }

std::string_view OrderCancelMessage::name() const { return "Order Cancel Message"; }

std::size_t OrderCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderCancelMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    cancelled_contracts_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t OrderCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderCancelMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(cancelled_contracts_));
    offset += 4;

    return offset;
}

std::size_t OrderCancelMessage::encoded_size() const {
    return wire_size;
}

void OrderCancelMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> OrderCancelMessage::clone() const {
    return std::make_unique<OrderCancelMessage>(*this);
}

void OrderCancelMessage::print(std::ostream& out) const {
    out << "OrderCancelMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", cancelled_contracts=";
    out << cancelled_contracts_;
    out << '}';
}

bool OrderCancelMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const OrderCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderCancelMessage::operator==(const OrderCancelMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && order_reference_number_ == other.order_reference_number_
        && cancelled_contracts_ == other.cancelled_contracts_;
}

bool OrderCancelMessage::operator!=(const OrderCancelMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
