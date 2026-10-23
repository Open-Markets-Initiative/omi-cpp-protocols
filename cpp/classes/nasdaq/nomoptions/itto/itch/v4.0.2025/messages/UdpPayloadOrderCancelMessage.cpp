#include "UdpPayloadOrderCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadOrderCancelMessage::UdpPayloadOrderCancelMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, std::uint32_t cancelled_contracts)
  : tracking_number_(tracking_number), timestamp_(timestamp), order_reference_number_(order_reference_number), cancelled_contracts_(cancelled_contracts) {}

std::uint16_t UdpPayloadOrderCancelMessage::tracking_number() const { return tracking_number_; }
void UdpPayloadOrderCancelMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadOrderCancelMessage::timestamp() const { return timestamp_; }
void UdpPayloadOrderCancelMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t UdpPayloadOrderCancelMessage::order_reference_number() const { return order_reference_number_; }
void UdpPayloadOrderCancelMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

std::uint32_t UdpPayloadOrderCancelMessage::cancelled_contracts() const { return cancelled_contracts_; }
void UdpPayloadOrderCancelMessage::set_cancelled_contracts(std::uint32_t value) { cancelled_contracts_ = value; }

PacketMessageCode UdpPayloadOrderCancelMessage::type() const { return message_type; }

std::string_view UdpPayloadOrderCancelMessage::name() const { return "Order Cancel Message"; }

std::size_t UdpPayloadOrderCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadOrderCancelMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    cancelled_contracts_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t UdpPayloadOrderCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadOrderCancelMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(cancelled_contracts_));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadOrderCancelMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadOrderCancelMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadOrderCancelMessage::clone() const {
    return std::make_unique<UdpPayloadOrderCancelMessage>(*this);
}

void UdpPayloadOrderCancelMessage::print(std::ostream& out) const {
    out << "UdpPayloadOrderCancelMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", cancelled_contracts=";
    out << cancelled_contracts_;
    out << '}';
}

bool UdpPayloadOrderCancelMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadOrderCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadOrderCancelMessage::operator==(const UdpPayloadOrderCancelMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && order_reference_number_ == other.order_reference_number_
        && cancelled_contracts_ == other.cancelled_contracts_;
}

bool UdpPayloadOrderCancelMessage::operator!=(const UdpPayloadOrderCancelMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
