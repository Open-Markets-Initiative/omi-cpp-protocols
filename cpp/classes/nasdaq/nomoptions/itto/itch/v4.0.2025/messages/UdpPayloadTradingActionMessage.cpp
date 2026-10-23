#include "UdpPayloadTradingActionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadTradingActionMessage::UdpPayloadTradingActionMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint32_t option_id, CurrentTradingState current_trading_state)
  : tracking_number_(tracking_number), timestamp_(timestamp), option_id_(option_id), current_trading_state_(current_trading_state) {}

std::uint16_t UdpPayloadTradingActionMessage::tracking_number() const { return tracking_number_; }
void UdpPayloadTradingActionMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadTradingActionMessage::timestamp() const { return timestamp_; }
void UdpPayloadTradingActionMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint32_t UdpPayloadTradingActionMessage::option_id() const { return option_id_; }
void UdpPayloadTradingActionMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

CurrentTradingState UdpPayloadTradingActionMessage::current_trading_state() const { return current_trading_state_; }
void UdpPayloadTradingActionMessage::set_current_trading_state(CurrentTradingState value) { current_trading_state_ = value; }

PacketMessageCode UdpPayloadTradingActionMessage::type() const { return message_type; }

std::string_view UdpPayloadTradingActionMessage::name() const { return "Trading Action Message"; }

std::size_t UdpPayloadTradingActionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadTradingActionMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    current_trading_state_ = static_cast<CurrentTradingState>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t UdpPayloadTradingActionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadTradingActionMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(current_trading_state_));
    offset += 1;

    return offset;
}

std::size_t UdpPayloadTradingActionMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadTradingActionMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadTradingActionMessage::clone() const {
    return std::make_unique<UdpPayloadTradingActionMessage>(*this);
}

void UdpPayloadTradingActionMessage::print(std::ostream& out) const {
    out << "UdpPayloadTradingActionMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", current_trading_state=";
    out << current_trading_state_;
    out << '}';
}

bool UdpPayloadTradingActionMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadTradingActionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadTradingActionMessage::operator==(const UdpPayloadTradingActionMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && option_id_ == other.option_id_
        && current_trading_state_ == other.current_trading_state_;
}

bool UdpPayloadTradingActionMessage::operator!=(const UdpPayloadTradingActionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
