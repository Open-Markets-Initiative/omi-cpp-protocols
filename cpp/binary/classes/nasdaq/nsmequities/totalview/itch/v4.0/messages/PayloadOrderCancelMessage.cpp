#include "PayloadOrderCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

PayloadOrderCancelMessage::PayloadOrderCancelMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_reference_number, std::uint32_t canceled_shares)
  : nanoseconds_(nanoseconds), order_reference_number_(order_reference_number), canceled_shares_(canceled_shares) {}

std::chrono::nanoseconds PayloadOrderCancelMessage::nanoseconds() const { return nanoseconds_; }
void PayloadOrderCancelMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t PayloadOrderCancelMessage::order_reference_number() const { return order_reference_number_; }
void PayloadOrderCancelMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

std::uint32_t PayloadOrderCancelMessage::canceled_shares() const { return canceled_shares_; }
void PayloadOrderCancelMessage::set_canceled_shares(std::uint32_t value) { canceled_shares_ = value; }

PacketMessageCode PayloadOrderCancelMessage::type() const { return message_type; }

std::string_view PayloadOrderCancelMessage::name() const { return "Order Cancel Message"; }

std::size_t PayloadOrderCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadOrderCancelMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    canceled_shares_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t PayloadOrderCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadOrderCancelMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(canceled_shares_));
    offset += 4;

    return offset;
}

std::size_t PayloadOrderCancelMessage::encoded_size() const {
    return wire_size;
}

void PayloadOrderCancelMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadOrderCancelMessage::clone() const {
    return std::make_unique<PayloadOrderCancelMessage>(*this);
}

void PayloadOrderCancelMessage::print(std::ostream& out) const {
    out << "PayloadOrderCancelMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", canceled_shares=";
    out << canceled_shares_;
    out << '}';
}

bool PayloadOrderCancelMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadOrderCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadOrderCancelMessage::operator==(const PayloadOrderCancelMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_reference_number_ == other.order_reference_number_
        && canceled_shares_ == other.canceled_shares_;
}

bool PayloadOrderCancelMessage::operator!=(const PayloadOrderCancelMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
