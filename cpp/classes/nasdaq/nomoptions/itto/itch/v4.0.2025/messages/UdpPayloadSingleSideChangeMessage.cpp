#include "UdpPayloadSingleSideChangeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadSingleSideChangeMessage::UdpPayloadSingleSideChangeMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t reference_number, ChangeReason change_reason, Decimal price_long, std::uint32_t volume_long)
  : tracking_number_(tracking_number), timestamp_(timestamp), reference_number_(reference_number), change_reason_(change_reason), price_long_(price_long), volume_long_(volume_long) {}

std::uint16_t UdpPayloadSingleSideChangeMessage::tracking_number() const { return tracking_number_; }
void UdpPayloadSingleSideChangeMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadSingleSideChangeMessage::timestamp() const { return timestamp_; }
void UdpPayloadSingleSideChangeMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t UdpPayloadSingleSideChangeMessage::reference_number() const { return reference_number_; }
void UdpPayloadSingleSideChangeMessage::set_reference_number(std::uint64_t value) { reference_number_ = value; }

ChangeReason UdpPayloadSingleSideChangeMessage::change_reason() const { return change_reason_; }
void UdpPayloadSingleSideChangeMessage::set_change_reason(ChangeReason value) { change_reason_ = value; }

Decimal UdpPayloadSingleSideChangeMessage::price_long() const { return price_long_; }
void UdpPayloadSingleSideChangeMessage::set_price_long(Decimal value) { price_long_ = value; }

std::uint32_t UdpPayloadSingleSideChangeMessage::volume_long() const { return volume_long_; }
void UdpPayloadSingleSideChangeMessage::set_volume_long(std::uint32_t value) { volume_long_ = value; }

PacketMessageCode UdpPayloadSingleSideChangeMessage::type() const { return message_type; }

std::string_view UdpPayloadSingleSideChangeMessage::name() const { return "Single Side Change Message"; }

std::size_t UdpPayloadSingleSideChangeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadSingleSideChangeMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    change_reason_ = static_cast<ChangeReason>(wire::read_char(data + offset));
    offset += 1;

    price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    volume_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t UdpPayloadSingleSideChangeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadSingleSideChangeMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(reference_number_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(change_reason_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_long_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(volume_long_));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadSingleSideChangeMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadSingleSideChangeMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadSingleSideChangeMessage::clone() const {
    return std::make_unique<UdpPayloadSingleSideChangeMessage>(*this);
}

void UdpPayloadSingleSideChangeMessage::print(std::ostream& out) const {
    out << "UdpPayloadSingleSideChangeMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", reference_number=";
    out << reference_number_;
    out << ", change_reason=";
    out << change_reason_;
    out << ", price_long=";
    out << price_long_;
    out << ", volume_long=";
    out << volume_long_;
    out << '}';
}

bool UdpPayloadSingleSideChangeMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadSingleSideChangeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadSingleSideChangeMessage::operator==(const UdpPayloadSingleSideChangeMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && reference_number_ == other.reference_number_
        && change_reason_ == other.change_reason_
        && price_long_ == other.price_long_
        && volume_long_ == other.volume_long_;
}

bool UdpPayloadSingleSideChangeMessage::operator!=(const UdpPayloadSingleSideChangeMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
