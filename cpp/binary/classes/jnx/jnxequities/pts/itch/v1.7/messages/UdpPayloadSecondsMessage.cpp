#include "UdpPayloadSecondsMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

UdpPayloadSecondsMessage::UdpPayloadSecondsMessage(std::chrono::seconds seconds)
  : seconds_(seconds) {}

std::chrono::seconds UdpPayloadSecondsMessage::seconds() const { return seconds_; }
void UdpPayloadSecondsMessage::set_seconds(std::chrono::seconds value) { seconds_ = value; }
std::int64_t UdpPayloadSecondsMessage::seconds_utc(const calendar::Day& day) const { return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(seconds_.count()) * 1000000000); }

PacketMessageCode UdpPayloadSecondsMessage::type() const { return message_type; }

std::string_view UdpPayloadSecondsMessage::name() const { return "Seconds Message"; }

std::size_t UdpPayloadSecondsMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadSecondsMessage", wire_size, length);

    seconds_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadSecondsMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadSecondsMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(seconds_.count()));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadSecondsMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadSecondsMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadSecondsMessage::clone() const {
    return std::make_unique<UdpPayloadSecondsMessage>(*this);
}

void UdpPayloadSecondsMessage::print(std::ostream& out) const {
    out << "UdpPayloadSecondsMessage{";
    out << "seconds=";
    calendar::print(out, seconds_.count(), 1000000000, "Asia/Tokyo");
    out << '}';
}

bool UdpPayloadSecondsMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadSecondsMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadSecondsMessage::operator==(const UdpPayloadSecondsMessage& other) const {
    return seconds_ == other.seconds_;
}

bool UdpPayloadSecondsMessage::operator!=(const UdpPayloadSecondsMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_7
