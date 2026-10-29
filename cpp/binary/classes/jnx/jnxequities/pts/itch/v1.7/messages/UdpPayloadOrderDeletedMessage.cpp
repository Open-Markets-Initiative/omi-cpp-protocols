#include "UdpPayloadOrderDeletedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

UdpPayloadOrderDeletedMessage::UdpPayloadOrderDeletedMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_number)
  : nanoseconds_(nanoseconds), order_number_(order_number) {}

std::chrono::nanoseconds UdpPayloadOrderDeletedMessage::nanoseconds() const { return nanoseconds_; }
void UdpPayloadOrderDeletedMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t UdpPayloadOrderDeletedMessage::order_number() const { return order_number_; }
void UdpPayloadOrderDeletedMessage::set_order_number(std::uint64_t value) { order_number_ = value; }

PacketMessageCode UdpPayloadOrderDeletedMessage::type() const { return message_type; }

std::string_view UdpPayloadOrderDeletedMessage::name() const { return "Order Deleted Message"; }

std::size_t UdpPayloadOrderDeletedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadOrderDeletedMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t UdpPayloadOrderDeletedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadOrderDeletedMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_number_));
    offset += 8;

    return offset;
}

std::size_t UdpPayloadOrderDeletedMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadOrderDeletedMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadOrderDeletedMessage::clone() const {
    return std::make_unique<UdpPayloadOrderDeletedMessage>(*this);
}

void UdpPayloadOrderDeletedMessage::print(std::ostream& out) const {
    out << "UdpPayloadOrderDeletedMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_number=";
    out << order_number_;
    out << '}';
}

bool UdpPayloadOrderDeletedMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadOrderDeletedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadOrderDeletedMessage::operator==(const UdpPayloadOrderDeletedMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_number_ == other.order_number_;
}

bool UdpPayloadOrderDeletedMessage::operator!=(const UdpPayloadOrderDeletedMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_7
