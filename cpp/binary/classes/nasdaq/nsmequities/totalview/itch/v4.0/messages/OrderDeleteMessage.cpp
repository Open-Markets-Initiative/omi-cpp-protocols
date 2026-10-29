#include "OrderDeleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

OrderDeleteMessage::OrderDeleteMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_reference_number)
  : nanoseconds_(nanoseconds), order_reference_number_(order_reference_number) {}

std::chrono::nanoseconds OrderDeleteMessage::nanoseconds() const { return nanoseconds_; }
void OrderDeleteMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t OrderDeleteMessage::order_reference_number() const { return order_reference_number_; }
void OrderDeleteMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

SequencedMessageCode OrderDeleteMessage::type() const { return message_type; }

std::string_view OrderDeleteMessage::name() const { return "Order Delete Message"; }

std::size_t OrderDeleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderDeleteMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t OrderDeleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderDeleteMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    return offset;
}

std::size_t OrderDeleteMessage::encoded_size() const {
    return wire_size;
}

void OrderDeleteMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> OrderDeleteMessage::clone() const {
    return std::make_unique<OrderDeleteMessage>(*this);
}

void OrderDeleteMessage::print(std::ostream& out) const {
    out << "OrderDeleteMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << '}';
}

bool OrderDeleteMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const OrderDeleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderDeleteMessage::operator==(const OrderDeleteMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_reference_number_ == other.order_reference_number_;
}

bool OrderDeleteMessage::operator!=(const OrderDeleteMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
