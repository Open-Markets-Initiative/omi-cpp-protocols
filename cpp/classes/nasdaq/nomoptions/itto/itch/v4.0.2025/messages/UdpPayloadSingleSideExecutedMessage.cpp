#include "UdpPayloadSingleSideExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadSingleSideExecutedMessage::UdpPayloadSingleSideExecutedMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t reference_number, std::uint32_t executed_contracts, std::uint32_t cross_number, std::uint32_t match_number)
  : tracking_number_(tracking_number), timestamp_(timestamp), reference_number_(reference_number), executed_contracts_(executed_contracts), cross_number_(cross_number), match_number_(match_number) {}

std::uint16_t UdpPayloadSingleSideExecutedMessage::tracking_number() const { return tracking_number_; }
void UdpPayloadSingleSideExecutedMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadSingleSideExecutedMessage::timestamp() const { return timestamp_; }
void UdpPayloadSingleSideExecutedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t UdpPayloadSingleSideExecutedMessage::reference_number() const { return reference_number_; }
void UdpPayloadSingleSideExecutedMessage::set_reference_number(std::uint64_t value) { reference_number_ = value; }

std::uint32_t UdpPayloadSingleSideExecutedMessage::executed_contracts() const { return executed_contracts_; }
void UdpPayloadSingleSideExecutedMessage::set_executed_contracts(std::uint32_t value) { executed_contracts_ = value; }

std::uint32_t UdpPayloadSingleSideExecutedMessage::cross_number() const { return cross_number_; }
void UdpPayloadSingleSideExecutedMessage::set_cross_number(std::uint32_t value) { cross_number_ = value; }

std::uint32_t UdpPayloadSingleSideExecutedMessage::match_number() const { return match_number_; }
void UdpPayloadSingleSideExecutedMessage::set_match_number(std::uint32_t value) { match_number_ = value; }

PacketMessageCode UdpPayloadSingleSideExecutedMessage::type() const { return message_type; }

std::string_view UdpPayloadSingleSideExecutedMessage::name() const { return "Single Side Executed Message"; }

std::size_t UdpPayloadSingleSideExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadSingleSideExecutedMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    executed_contracts_ = wire::read_u32_be(data + offset);
    offset += 4;

    cross_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    match_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t UdpPayloadSingleSideExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadSingleSideExecutedMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(executed_contracts_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(cross_number_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(match_number_));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadSingleSideExecutedMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadSingleSideExecutedMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadSingleSideExecutedMessage::clone() const {
    return std::make_unique<UdpPayloadSingleSideExecutedMessage>(*this);
}

void UdpPayloadSingleSideExecutedMessage::print(std::ostream& out) const {
    out << "UdpPayloadSingleSideExecutedMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", reference_number=";
    out << reference_number_;
    out << ", executed_contracts=";
    out << executed_contracts_;
    out << ", cross_number=";
    out << cross_number_;
    out << ", match_number=";
    out << match_number_;
    out << '}';
}

bool UdpPayloadSingleSideExecutedMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadSingleSideExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadSingleSideExecutedMessage::operator==(const UdpPayloadSingleSideExecutedMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && reference_number_ == other.reference_number_
        && executed_contracts_ == other.executed_contracts_
        && cross_number_ == other.cross_number_
        && match_number_ == other.match_number_;
}

bool UdpPayloadSingleSideExecutedMessage::operator!=(const UdpPayloadSingleSideExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
