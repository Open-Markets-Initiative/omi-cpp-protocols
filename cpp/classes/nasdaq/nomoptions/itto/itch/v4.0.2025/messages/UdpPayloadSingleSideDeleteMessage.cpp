#include "UdpPayloadSingleSideDeleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadSingleSideDeleteMessage::UdpPayloadSingleSideDeleteMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t reference_number)
  : tracking_number_(tracking_number), timestamp_(timestamp), reference_number_(reference_number) {}

std::uint16_t UdpPayloadSingleSideDeleteMessage::tracking_number() const { return tracking_number_; }
void UdpPayloadSingleSideDeleteMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadSingleSideDeleteMessage::timestamp() const { return timestamp_; }
void UdpPayloadSingleSideDeleteMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t UdpPayloadSingleSideDeleteMessage::reference_number() const { return reference_number_; }
void UdpPayloadSingleSideDeleteMessage::set_reference_number(std::uint64_t value) { reference_number_ = value; }

PacketMessageCode UdpPayloadSingleSideDeleteMessage::type() const { return message_type; }

std::string_view UdpPayloadSingleSideDeleteMessage::name() const { return "Single Side Delete Message"; }

std::size_t UdpPayloadSingleSideDeleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadSingleSideDeleteMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t UdpPayloadSingleSideDeleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadSingleSideDeleteMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(reference_number_));
    offset += 8;

    return offset;
}

std::size_t UdpPayloadSingleSideDeleteMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadSingleSideDeleteMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadSingleSideDeleteMessage::clone() const {
    return std::make_unique<UdpPayloadSingleSideDeleteMessage>(*this);
}

void UdpPayloadSingleSideDeleteMessage::print(std::ostream& out) const {
    out << "UdpPayloadSingleSideDeleteMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", reference_number=";
    out << reference_number_;
    out << '}';
}

bool UdpPayloadSingleSideDeleteMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadSingleSideDeleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadSingleSideDeleteMessage::operator==(const UdpPayloadSingleSideDeleteMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && reference_number_ == other.reference_number_;
}

bool UdpPayloadSingleSideDeleteMessage::operator!=(const UdpPayloadSingleSideDeleteMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
