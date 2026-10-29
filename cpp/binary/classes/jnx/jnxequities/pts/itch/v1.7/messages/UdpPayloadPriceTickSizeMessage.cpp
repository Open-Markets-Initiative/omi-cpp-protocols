#include "UdpPayloadPriceTickSizeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

UdpPayloadPriceTickSizeMessage::UdpPayloadPriceTickSizeMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t price_tick_size_table_id, Decimal price_tick_size, Decimal price_start)
  : nanoseconds_(nanoseconds), price_tick_size_table_id_(price_tick_size_table_id), price_tick_size_(price_tick_size), price_start_(price_start) {}

std::chrono::nanoseconds UdpPayloadPriceTickSizeMessage::nanoseconds() const { return nanoseconds_; }
void UdpPayloadPriceTickSizeMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t UdpPayloadPriceTickSizeMessage::price_tick_size_table_id() const { return price_tick_size_table_id_; }
void UdpPayloadPriceTickSizeMessage::set_price_tick_size_table_id(std::uint32_t value) { price_tick_size_table_id_ = value; }

Decimal UdpPayloadPriceTickSizeMessage::price_tick_size() const { return price_tick_size_; }
void UdpPayloadPriceTickSizeMessage::set_price_tick_size(Decimal value) { price_tick_size_ = value; }

Decimal UdpPayloadPriceTickSizeMessage::price_start() const { return price_start_; }
void UdpPayloadPriceTickSizeMessage::set_price_start(Decimal value) { price_start_ = value; }

PacketMessageCode UdpPayloadPriceTickSizeMessage::type() const { return message_type; }

std::string_view UdpPayloadPriceTickSizeMessage::name() const { return "Price Tick Size Message"; }

std::size_t UdpPayloadPriceTickSizeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadPriceTickSizeMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    price_tick_size_table_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_tick_size_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -1);
    offset += 4;

    price_start_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -1);
    offset += 4;

    return offset;
}

std::size_t UdpPayloadPriceTickSizeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadPriceTickSizeMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_tick_size_table_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_tick_size_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_start_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadPriceTickSizeMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadPriceTickSizeMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadPriceTickSizeMessage::clone() const {
    return std::make_unique<UdpPayloadPriceTickSizeMessage>(*this);
}

void UdpPayloadPriceTickSizeMessage::print(std::ostream& out) const {
    out << "UdpPayloadPriceTickSizeMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", price_tick_size_table_id=";
    out << price_tick_size_table_id_;
    out << ", price_tick_size=";
    out << price_tick_size_;
    out << ", price_start=";
    out << price_start_;
    out << '}';
}

bool UdpPayloadPriceTickSizeMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadPriceTickSizeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadPriceTickSizeMessage::operator==(const UdpPayloadPriceTickSizeMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && price_tick_size_table_id_ == other.price_tick_size_table_id_
        && price_tick_size_ == other.price_tick_size_
        && price_start_ == other.price_start_;
}

bool UdpPayloadPriceTickSizeMessage::operator!=(const UdpPayloadPriceTickSizeMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_7
