#include "OrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

OrderExecutedMessage::OrderExecutedMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_number, std::uint32_t executed_quantity, std::uint64_t match_number)
  : nanoseconds_(nanoseconds), order_number_(order_number), executed_quantity_(executed_quantity), match_number_(match_number) {}

std::chrono::nanoseconds OrderExecutedMessage::nanoseconds() const { return nanoseconds_; }
void OrderExecutedMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t OrderExecutedMessage::order_number() const { return order_number_; }
void OrderExecutedMessage::set_order_number(std::uint64_t value) { order_number_ = value; }

std::uint32_t OrderExecutedMessage::executed_quantity() const { return executed_quantity_; }
void OrderExecutedMessage::set_executed_quantity(std::uint32_t value) { executed_quantity_ = value; }

std::uint64_t OrderExecutedMessage::match_number() const { return match_number_; }
void OrderExecutedMessage::set_match_number(std::uint64_t value) { match_number_ = value; }

MessageCode OrderExecutedMessage::type() const { return message_type; }

std::string_view OrderExecutedMessage::name() const { return "Order Executed Message"; }

std::size_t OrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    executed_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    match_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t OrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(executed_quantity_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(match_number_));
    offset += 8;

    return offset;
}

std::size_t OrderExecutedMessage::encoded_size() const {
    return wire_size;
}

void OrderExecutedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderExecutedMessage::clone() const {
    return std::make_unique<OrderExecutedMessage>(*this);
}

void OrderExecutedMessage::print(std::ostream& out) const {
    out << "OrderExecutedMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_number=";
    out << order_number_;
    out << ", executed_quantity=";
    out << executed_quantity_;
    out << ", match_number=";
    out << match_number_;
    out << '}';
}

bool OrderExecutedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedMessage::operator==(const OrderExecutedMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_number_ == other.order_number_
        && executed_quantity_ == other.executed_quantity_
        && match_number_ == other.match_number_;
}

bool OrderExecutedMessage::operator!=(const OrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_6
