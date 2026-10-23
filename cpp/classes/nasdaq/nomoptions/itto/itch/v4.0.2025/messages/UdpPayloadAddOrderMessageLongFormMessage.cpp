#include "UdpPayloadAddOrderMessageLongFormMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadAddOrderMessageLongFormMessage::UdpPayloadAddOrderMessageLongFormMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, MarketSide market_side, std::uint32_t option_id, Decimal price_long, std::uint32_t volume_long)
  : tracking_number_(tracking_number), timestamp_(timestamp), order_reference_number_(order_reference_number), market_side_(market_side), option_id_(option_id), price_long_(price_long), volume_long_(volume_long) {}

std::uint16_t UdpPayloadAddOrderMessageLongFormMessage::tracking_number() const { return tracking_number_; }
void UdpPayloadAddOrderMessageLongFormMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadAddOrderMessageLongFormMessage::timestamp() const { return timestamp_; }
void UdpPayloadAddOrderMessageLongFormMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t UdpPayloadAddOrderMessageLongFormMessage::order_reference_number() const { return order_reference_number_; }
void UdpPayloadAddOrderMessageLongFormMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

MarketSide UdpPayloadAddOrderMessageLongFormMessage::market_side() const { return market_side_; }
void UdpPayloadAddOrderMessageLongFormMessage::set_market_side(MarketSide value) { market_side_ = value; }

std::uint32_t UdpPayloadAddOrderMessageLongFormMessage::option_id() const { return option_id_; }
void UdpPayloadAddOrderMessageLongFormMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

Decimal UdpPayloadAddOrderMessageLongFormMessage::price_long() const { return price_long_; }
void UdpPayloadAddOrderMessageLongFormMessage::set_price_long(Decimal value) { price_long_ = value; }

std::uint32_t UdpPayloadAddOrderMessageLongFormMessage::volume_long() const { return volume_long_; }
void UdpPayloadAddOrderMessageLongFormMessage::set_volume_long(std::uint32_t value) { volume_long_ = value; }

PacketMessageCode UdpPayloadAddOrderMessageLongFormMessage::type() const { return message_type; }

std::string_view UdpPayloadAddOrderMessageLongFormMessage::name() const { return "Add Order Message Long Form Message"; }

std::size_t UdpPayloadAddOrderMessageLongFormMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadAddOrderMessageLongFormMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    market_side_ = static_cast<MarketSide>(wire::read_char(data + offset));
    offset += 1;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    volume_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t UdpPayloadAddOrderMessageLongFormMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadAddOrderMessageLongFormMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(market_side_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_long_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(volume_long_));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadAddOrderMessageLongFormMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadAddOrderMessageLongFormMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadAddOrderMessageLongFormMessage::clone() const {
    return std::make_unique<UdpPayloadAddOrderMessageLongFormMessage>(*this);
}

void UdpPayloadAddOrderMessageLongFormMessage::print(std::ostream& out) const {
    out << "UdpPayloadAddOrderMessageLongFormMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", market_side=";
    out << market_side_;
    out << ", option_id=";
    out << option_id_;
    out << ", price_long=";
    out << price_long_;
    out << ", volume_long=";
    out << volume_long_;
    out << '}';
}

bool UdpPayloadAddOrderMessageLongFormMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadAddOrderMessageLongFormMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadAddOrderMessageLongFormMessage::operator==(const UdpPayloadAddOrderMessageLongFormMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && order_reference_number_ == other.order_reference_number_
        && market_side_ == other.market_side_
        && option_id_ == other.option_id_
        && price_long_ == other.price_long_
        && volume_long_ == other.volume_long_;
}

bool UdpPayloadAddOrderMessageLongFormMessage::operator!=(const UdpPayloadAddOrderMessageLongFormMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
