#include "UdpPayloadOptionsCrossTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadOptionsCrossTradeMessage::UdpPayloadOptionsCrossTradeMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint32_t option_id, std::uint32_t cross_number, std::uint32_t match_number, CrossType cross_type, Decimal price_long, std::uint32_t volume_long)
  : tracking_number_(tracking_number), timestamp_(timestamp), option_id_(option_id), cross_number_(cross_number), match_number_(match_number), cross_type_(cross_type), price_long_(price_long), volume_long_(volume_long) {}

std::uint16_t UdpPayloadOptionsCrossTradeMessage::tracking_number() const { return tracking_number_; }
void UdpPayloadOptionsCrossTradeMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadOptionsCrossTradeMessage::timestamp() const { return timestamp_; }
void UdpPayloadOptionsCrossTradeMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint32_t UdpPayloadOptionsCrossTradeMessage::option_id() const { return option_id_; }
void UdpPayloadOptionsCrossTradeMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

std::uint32_t UdpPayloadOptionsCrossTradeMessage::cross_number() const { return cross_number_; }
void UdpPayloadOptionsCrossTradeMessage::set_cross_number(std::uint32_t value) { cross_number_ = value; }

std::uint32_t UdpPayloadOptionsCrossTradeMessage::match_number() const { return match_number_; }
void UdpPayloadOptionsCrossTradeMessage::set_match_number(std::uint32_t value) { match_number_ = value; }

CrossType UdpPayloadOptionsCrossTradeMessage::cross_type() const { return cross_type_; }
void UdpPayloadOptionsCrossTradeMessage::set_cross_type(CrossType value) { cross_type_ = value; }

Decimal UdpPayloadOptionsCrossTradeMessage::price_long() const { return price_long_; }
void UdpPayloadOptionsCrossTradeMessage::set_price_long(Decimal value) { price_long_ = value; }

std::uint32_t UdpPayloadOptionsCrossTradeMessage::volume_long() const { return volume_long_; }
void UdpPayloadOptionsCrossTradeMessage::set_volume_long(std::uint32_t value) { volume_long_ = value; }

PacketMessageCode UdpPayloadOptionsCrossTradeMessage::type() const { return message_type; }

std::string_view UdpPayloadOptionsCrossTradeMessage::name() const { return "Options Cross Trade Message"; }

std::size_t UdpPayloadOptionsCrossTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadOptionsCrossTradeMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    cross_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    match_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    cross_type_ = static_cast<CrossType>(wire::read_char(data + offset));
    offset += 1;

    price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    volume_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t UdpPayloadOptionsCrossTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadOptionsCrossTradeMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(cross_number_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(match_number_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(cross_type_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_long_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(volume_long_));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadOptionsCrossTradeMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadOptionsCrossTradeMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadOptionsCrossTradeMessage::clone() const {
    return std::make_unique<UdpPayloadOptionsCrossTradeMessage>(*this);
}

void UdpPayloadOptionsCrossTradeMessage::print(std::ostream& out) const {
    out << "UdpPayloadOptionsCrossTradeMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", cross_number=";
    out << cross_number_;
    out << ", match_number=";
    out << match_number_;
    out << ", cross_type=";
    out << cross_type_;
    out << ", price_long=";
    out << price_long_;
    out << ", volume_long=";
    out << volume_long_;
    out << '}';
}

bool UdpPayloadOptionsCrossTradeMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadOptionsCrossTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadOptionsCrossTradeMessage::operator==(const UdpPayloadOptionsCrossTradeMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && option_id_ == other.option_id_
        && cross_number_ == other.cross_number_
        && match_number_ == other.match_number_
        && cross_type_ == other.cross_type_
        && price_long_ == other.price_long_
        && volume_long_ == other.volume_long_;
}

bool UdpPayloadOptionsCrossTradeMessage::operator!=(const UdpPayloadOptionsCrossTradeMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
