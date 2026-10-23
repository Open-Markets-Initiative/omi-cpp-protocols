#include "UdpPayloadBrokenTradeOrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadBrokenTradeOrderExecutedMessage::UdpPayloadBrokenTradeOrderExecutedMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint32_t cross_number, std::uint32_t match_number)
  : tracking_number_(tracking_number), timestamp_(timestamp), cross_number_(cross_number), match_number_(match_number) {}

std::uint16_t UdpPayloadBrokenTradeOrderExecutedMessage::tracking_number() const { return tracking_number_; }
void UdpPayloadBrokenTradeOrderExecutedMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadBrokenTradeOrderExecutedMessage::timestamp() const { return timestamp_; }
void UdpPayloadBrokenTradeOrderExecutedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint32_t UdpPayloadBrokenTradeOrderExecutedMessage::cross_number() const { return cross_number_; }
void UdpPayloadBrokenTradeOrderExecutedMessage::set_cross_number(std::uint32_t value) { cross_number_ = value; }

std::uint32_t UdpPayloadBrokenTradeOrderExecutedMessage::match_number() const { return match_number_; }
void UdpPayloadBrokenTradeOrderExecutedMessage::set_match_number(std::uint32_t value) { match_number_ = value; }

PacketMessageCode UdpPayloadBrokenTradeOrderExecutedMessage::type() const { return message_type; }

std::string_view UdpPayloadBrokenTradeOrderExecutedMessage::name() const { return "Broken Trade Order Executed Message"; }

std::size_t UdpPayloadBrokenTradeOrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadBrokenTradeOrderExecutedMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    cross_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    match_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t UdpPayloadBrokenTradeOrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadBrokenTradeOrderExecutedMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(cross_number_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(match_number_));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadBrokenTradeOrderExecutedMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadBrokenTradeOrderExecutedMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadBrokenTradeOrderExecutedMessage::clone() const {
    return std::make_unique<UdpPayloadBrokenTradeOrderExecutedMessage>(*this);
}

void UdpPayloadBrokenTradeOrderExecutedMessage::print(std::ostream& out) const {
    out << "UdpPayloadBrokenTradeOrderExecutedMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", cross_number=";
    out << cross_number_;
    out << ", match_number=";
    out << match_number_;
    out << '}';
}

bool UdpPayloadBrokenTradeOrderExecutedMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadBrokenTradeOrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadBrokenTradeOrderExecutedMessage::operator==(const UdpPayloadBrokenTradeOrderExecutedMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && cross_number_ == other.cross_number_
        && match_number_ == other.match_number_;
}

bool UdpPayloadBrokenTradeOrderExecutedMessage::operator!=(const UdpPayloadBrokenTradeOrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
