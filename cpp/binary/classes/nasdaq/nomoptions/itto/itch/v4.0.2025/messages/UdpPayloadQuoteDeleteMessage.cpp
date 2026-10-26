#include "UdpPayloadQuoteDeleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadQuoteDeleteMessage::UdpPayloadQuoteDeleteMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t bid_reference_number, std::uint64_t ask_reference_number)
  : tracking_number_(tracking_number), timestamp_(timestamp), bid_reference_number_(bid_reference_number), ask_reference_number_(ask_reference_number) {}

std::uint16_t UdpPayloadQuoteDeleteMessage::tracking_number() const { return tracking_number_; }
void UdpPayloadQuoteDeleteMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadQuoteDeleteMessage::timestamp() const { return timestamp_; }
void UdpPayloadQuoteDeleteMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t UdpPayloadQuoteDeleteMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint64_t UdpPayloadQuoteDeleteMessage::bid_reference_number() const { return bid_reference_number_; }
void UdpPayloadQuoteDeleteMessage::set_bid_reference_number(std::uint64_t value) { bid_reference_number_ = value; }

std::uint64_t UdpPayloadQuoteDeleteMessage::ask_reference_number() const { return ask_reference_number_; }
void UdpPayloadQuoteDeleteMessage::set_ask_reference_number(std::uint64_t value) { ask_reference_number_ = value; }

PacketMessageCode UdpPayloadQuoteDeleteMessage::type() const { return message_type; }

std::string_view UdpPayloadQuoteDeleteMessage::name() const { return "Quote Delete Message"; }

std::size_t UdpPayloadQuoteDeleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadQuoteDeleteMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    bid_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    ask_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t UdpPayloadQuoteDeleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadQuoteDeleteMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(bid_reference_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(ask_reference_number_));
    offset += 8;

    return offset;
}

std::size_t UdpPayloadQuoteDeleteMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadQuoteDeleteMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadQuoteDeleteMessage::clone() const {
    return std::make_unique<UdpPayloadQuoteDeleteMessage>(*this);
}

void UdpPayloadQuoteDeleteMessage::print(std::ostream& out) const {
    out << "UdpPayloadQuoteDeleteMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", bid_reference_number=";
    out << bid_reference_number_;
    out << ", ask_reference_number=";
    out << ask_reference_number_;
    out << '}';
}

bool UdpPayloadQuoteDeleteMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadQuoteDeleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadQuoteDeleteMessage::operator==(const UdpPayloadQuoteDeleteMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && bid_reference_number_ == other.bid_reference_number_
        && ask_reference_number_ == other.ask_reference_number_;
}

bool UdpPayloadQuoteDeleteMessage::operator!=(const UdpPayloadQuoteDeleteMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
