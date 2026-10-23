#include "UdpPayloadSystemEventMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadSystemEventMessage::UdpPayloadSystemEventMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, EventCode event_code)
  : tracking_number_(tracking_number), timestamp_(timestamp), event_code_(event_code) {}

std::uint16_t UdpPayloadSystemEventMessage::tracking_number() const { return tracking_number_; }
void UdpPayloadSystemEventMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadSystemEventMessage::timestamp() const { return timestamp_; }
void UdpPayloadSystemEventMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

EventCode UdpPayloadSystemEventMessage::event_code() const { return event_code_; }
void UdpPayloadSystemEventMessage::set_event_code(EventCode value) { event_code_ = value; }

PacketMessageCode UdpPayloadSystemEventMessage::type() const { return message_type; }

std::string_view UdpPayloadSystemEventMessage::name() const { return "System Event Message"; }

std::size_t UdpPayloadSystemEventMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadSystemEventMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    event_code_ = static_cast<EventCode>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t UdpPayloadSystemEventMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadSystemEventMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_char(data + offset, static_cast<char>(event_code_));
    offset += 1;

    return offset;
}

std::size_t UdpPayloadSystemEventMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadSystemEventMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadSystemEventMessage::clone() const {
    return std::make_unique<UdpPayloadSystemEventMessage>(*this);
}

void UdpPayloadSystemEventMessage::print(std::ostream& out) const {
    out << "UdpPayloadSystemEventMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", event_code=";
    out << event_code_;
    out << '}';
}

bool UdpPayloadSystemEventMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadSystemEventMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadSystemEventMessage::operator==(const UdpPayloadSystemEventMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && event_code_ == other.event_code_;
}

bool UdpPayloadSystemEventMessage::operator!=(const UdpPayloadSystemEventMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
