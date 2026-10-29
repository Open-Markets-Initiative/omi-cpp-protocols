#include "UdpPayloadOrderReplacedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

UdpPayloadOrderReplacedMessage::UdpPayloadOrderReplacedMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t original_order_number, std::uint64_t new_order_number, std::uint32_t quantity, Decimal price)
  : nanoseconds_(nanoseconds), original_order_number_(original_order_number), new_order_number_(new_order_number), quantity_(quantity), price_(price) {}

std::chrono::nanoseconds UdpPayloadOrderReplacedMessage::nanoseconds() const { return nanoseconds_; }
void UdpPayloadOrderReplacedMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t UdpPayloadOrderReplacedMessage::original_order_number() const { return original_order_number_; }
void UdpPayloadOrderReplacedMessage::set_original_order_number(std::uint64_t value) { original_order_number_ = value; }

std::uint64_t UdpPayloadOrderReplacedMessage::new_order_number() const { return new_order_number_; }
void UdpPayloadOrderReplacedMessage::set_new_order_number(std::uint64_t value) { new_order_number_ = value; }

std::uint32_t UdpPayloadOrderReplacedMessage::quantity() const { return quantity_; }
void UdpPayloadOrderReplacedMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

Decimal UdpPayloadOrderReplacedMessage::price() const { return price_; }
void UdpPayloadOrderReplacedMessage::set_price(Decimal value) { price_ = value; }

PacketMessageCode UdpPayloadOrderReplacedMessage::type() const { return message_type; }

std::string_view UdpPayloadOrderReplacedMessage::name() const { return "Order Replaced Message"; }

std::size_t UdpPayloadOrderReplacedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadOrderReplacedMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    original_order_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    new_order_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -1);
    offset += 4;

    return offset;
}

std::size_t UdpPayloadOrderReplacedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadOrderReplacedMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(original_order_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(new_order_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadOrderReplacedMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadOrderReplacedMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadOrderReplacedMessage::clone() const {
    return std::make_unique<UdpPayloadOrderReplacedMessage>(*this);
}

void UdpPayloadOrderReplacedMessage::print(std::ostream& out) const {
    out << "UdpPayloadOrderReplacedMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", original_order_number=";
    out << original_order_number_;
    out << ", new_order_number=";
    out << new_order_number_;
    out << ", quantity=";
    out << quantity_;
    out << ", price=";
    out << price_;
    out << '}';
}

bool UdpPayloadOrderReplacedMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadOrderReplacedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadOrderReplacedMessage::operator==(const UdpPayloadOrderReplacedMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && original_order_number_ == other.original_order_number_
        && new_order_number_ == other.new_order_number_
        && quantity_ == other.quantity_
        && price_ == other.price_;
}

bool UdpPayloadOrderReplacedMessage::operator!=(const UdpPayloadOrderReplacedMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_7
