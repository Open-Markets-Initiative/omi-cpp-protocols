#include "OrderCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

OrderCancelMessage::OrderCancelMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_reference_number, std::uint32_t canceled_shares)
  : nanoseconds_(nanoseconds), order_reference_number_(order_reference_number), canceled_shares_(canceled_shares) {}

std::chrono::nanoseconds OrderCancelMessage::nanoseconds() const { return nanoseconds_; }
void OrderCancelMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t OrderCancelMessage::order_reference_number() const { return order_reference_number_; }
void OrderCancelMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

std::uint32_t OrderCancelMessage::canceled_shares() const { return canceled_shares_; }
void OrderCancelMessage::set_canceled_shares(std::uint32_t value) { canceled_shares_ = value; }

SequencedMessageCode OrderCancelMessage::type() const { return message_type; }

std::string_view OrderCancelMessage::name() const { return "Order Cancel Message"; }

std::size_t OrderCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderCancelMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    canceled_shares_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t OrderCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderCancelMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(canceled_shares_));
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
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", canceled_shares=";
    out << canceled_shares_;
    out << '}';
}

bool OrderCancelMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const OrderCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderCancelMessage::operator==(const OrderCancelMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_reference_number_ == other.order_reference_number_
        && canceled_shares_ == other.canceled_shares_;
}

bool OrderCancelMessage::operator!=(const OrderCancelMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
