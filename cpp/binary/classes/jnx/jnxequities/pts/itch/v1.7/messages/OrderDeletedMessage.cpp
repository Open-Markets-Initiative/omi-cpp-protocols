#include "OrderDeletedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

OrderDeletedMessage::OrderDeletedMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_number)
  : nanoseconds_(nanoseconds), order_number_(order_number) {}

std::chrono::nanoseconds OrderDeletedMessage::nanoseconds() const { return nanoseconds_; }
void OrderDeletedMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t OrderDeletedMessage::order_number() const { return order_number_; }
void OrderDeletedMessage::set_order_number(std::uint64_t value) { order_number_ = value; }

SequencedMessageCode OrderDeletedMessage::type() const { return message_type; }

std::string_view OrderDeletedMessage::name() const { return "Order Deleted Message"; }

std::size_t OrderDeletedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderDeletedMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t OrderDeletedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderDeletedMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_number_));
    offset += 8;

    return offset;
}

std::size_t OrderDeletedMessage::encoded_size() const {
    return wire_size;
}

void OrderDeletedMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> OrderDeletedMessage::clone() const {
    return std::make_unique<OrderDeletedMessage>(*this);
}

void OrderDeletedMessage::print(std::ostream& out) const {
    out << "OrderDeletedMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_number=";
    out << order_number_;
    out << '}';
}

bool OrderDeletedMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const OrderDeletedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderDeletedMessage::operator==(const OrderDeletedMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_number_ == other.order_number_;
}

bool OrderDeletedMessage::operator!=(const OrderDeletedMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_7
