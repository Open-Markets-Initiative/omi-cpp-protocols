#include "PayloadOrderDeleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

PayloadOrderDeleteMessage::PayloadOrderDeleteMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_reference_number)
  : nanoseconds_(nanoseconds), order_reference_number_(order_reference_number) {}

std::chrono::nanoseconds PayloadOrderDeleteMessage::nanoseconds() const { return nanoseconds_; }
void PayloadOrderDeleteMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t PayloadOrderDeleteMessage::order_reference_number() const { return order_reference_number_; }
void PayloadOrderDeleteMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

PacketMessageCode PayloadOrderDeleteMessage::type() const { return message_type; }

std::string_view PayloadOrderDeleteMessage::name() const { return "Order Delete Message"; }

std::size_t PayloadOrderDeleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadOrderDeleteMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t PayloadOrderDeleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadOrderDeleteMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    return offset;
}

std::size_t PayloadOrderDeleteMessage::encoded_size() const {
    return wire_size;
}

void PayloadOrderDeleteMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadOrderDeleteMessage::clone() const {
    return std::make_unique<PayloadOrderDeleteMessage>(*this);
}

void PayloadOrderDeleteMessage::print(std::ostream& out) const {
    out << "PayloadOrderDeleteMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << '}';
}

bool PayloadOrderDeleteMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadOrderDeleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadOrderDeleteMessage::operator==(const PayloadOrderDeleteMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_reference_number_ == other.order_reference_number_;
}

bool PayloadOrderDeleteMessage::operator!=(const PayloadOrderDeleteMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
