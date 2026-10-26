#include "UdpPayloadQuoteReplaceMessageShortForm.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadQuoteReplaceMessageShortForm::UdpPayloadQuoteReplaceMessageShortForm(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t original_bid_reference_number, std::uint64_t bid_reference_number, std::uint64_t original_ask_reference_number, std::uint64_t ask_reference_number, Decimal bid_price_short, std::uint16_t bid_size_short, Decimal ask_price_short, std::uint16_t ask_size_short)
  : tracking_number_(tracking_number), timestamp_(timestamp), original_bid_reference_number_(original_bid_reference_number), bid_reference_number_(bid_reference_number), original_ask_reference_number_(original_ask_reference_number), ask_reference_number_(ask_reference_number), bid_price_short_(bid_price_short), bid_size_short_(bid_size_short), ask_price_short_(ask_price_short), ask_size_short_(ask_size_short) {}

std::uint16_t UdpPayloadQuoteReplaceMessageShortForm::tracking_number() const { return tracking_number_; }
void UdpPayloadQuoteReplaceMessageShortForm::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadQuoteReplaceMessageShortForm::timestamp() const { return timestamp_; }
void UdpPayloadQuoteReplaceMessageShortForm::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t UdpPayloadQuoteReplaceMessageShortForm::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint64_t UdpPayloadQuoteReplaceMessageShortForm::original_bid_reference_number() const { return original_bid_reference_number_; }
void UdpPayloadQuoteReplaceMessageShortForm::set_original_bid_reference_number(std::uint64_t value) { original_bid_reference_number_ = value; }

std::uint64_t UdpPayloadQuoteReplaceMessageShortForm::bid_reference_number() const { return bid_reference_number_; }
void UdpPayloadQuoteReplaceMessageShortForm::set_bid_reference_number(std::uint64_t value) { bid_reference_number_ = value; }

std::uint64_t UdpPayloadQuoteReplaceMessageShortForm::original_ask_reference_number() const { return original_ask_reference_number_; }
void UdpPayloadQuoteReplaceMessageShortForm::set_original_ask_reference_number(std::uint64_t value) { original_ask_reference_number_ = value; }

std::uint64_t UdpPayloadQuoteReplaceMessageShortForm::ask_reference_number() const { return ask_reference_number_; }
void UdpPayloadQuoteReplaceMessageShortForm::set_ask_reference_number(std::uint64_t value) { ask_reference_number_ = value; }

Decimal UdpPayloadQuoteReplaceMessageShortForm::bid_price_short() const { return bid_price_short_; }
void UdpPayloadQuoteReplaceMessageShortForm::set_bid_price_short(Decimal value) { bid_price_short_ = value; }

std::uint16_t UdpPayloadQuoteReplaceMessageShortForm::bid_size_short() const { return bid_size_short_; }
void UdpPayloadQuoteReplaceMessageShortForm::set_bid_size_short(std::uint16_t value) { bid_size_short_ = value; }

Decimal UdpPayloadQuoteReplaceMessageShortForm::ask_price_short() const { return ask_price_short_; }
void UdpPayloadQuoteReplaceMessageShortForm::set_ask_price_short(Decimal value) { ask_price_short_ = value; }

std::uint16_t UdpPayloadQuoteReplaceMessageShortForm::ask_size_short() const { return ask_size_short_; }
void UdpPayloadQuoteReplaceMessageShortForm::set_ask_size_short(std::uint16_t value) { ask_size_short_ = value; }

PacketMessageCode UdpPayloadQuoteReplaceMessageShortForm::type() const { return message_type; }

std::string_view UdpPayloadQuoteReplaceMessageShortForm::name() const { return "Quote Replace Message Short Form"; }

std::size_t UdpPayloadQuoteReplaceMessageShortForm::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadQuoteReplaceMessageShortForm", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    original_bid_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    bid_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    original_ask_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    ask_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    bid_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -4);
    offset += 2;

    bid_size_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    ask_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -4);
    offset += 2;

    ask_size_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t UdpPayloadQuoteReplaceMessageShortForm::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadQuoteReplaceMessageShortForm", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(original_bid_reference_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(bid_reference_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(original_ask_reference_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(ask_reference_number_));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(bid_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(bid_size_short_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(ask_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(ask_size_short_));
    offset += 2;

    return offset;
}

std::size_t UdpPayloadQuoteReplaceMessageShortForm::encoded_size() const {
    return wire_size;
}

void UdpPayloadQuoteReplaceMessageShortForm::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadQuoteReplaceMessageShortForm::clone() const {
    return std::make_unique<UdpPayloadQuoteReplaceMessageShortForm>(*this);
}

void UdpPayloadQuoteReplaceMessageShortForm::print(std::ostream& out) const {
    out << "UdpPayloadQuoteReplaceMessageShortForm{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", original_bid_reference_number=";
    out << original_bid_reference_number_;
    out << ", bid_reference_number=";
    out << bid_reference_number_;
    out << ", original_ask_reference_number=";
    out << original_ask_reference_number_;
    out << ", ask_reference_number=";
    out << ask_reference_number_;
    out << ", bid_price_short=";
    out << bid_price_short_;
    out << ", bid_size_short=";
    out << bid_size_short_;
    out << ", ask_price_short=";
    out << ask_price_short_;
    out << ", ask_size_short=";
    out << ask_size_short_;
    out << '}';
}

bool UdpPayloadQuoteReplaceMessageShortForm::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadQuoteReplaceMessageShortForm*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadQuoteReplaceMessageShortForm::operator==(const UdpPayloadQuoteReplaceMessageShortForm& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && original_bid_reference_number_ == other.original_bid_reference_number_
        && bid_reference_number_ == other.bid_reference_number_
        && original_ask_reference_number_ == other.original_ask_reference_number_
        && ask_reference_number_ == other.ask_reference_number_
        && bid_price_short_ == other.bid_price_short_
        && bid_size_short_ == other.bid_size_short_
        && ask_price_short_ == other.ask_price_short_
        && ask_size_short_ == other.ask_size_short_;
}

bool UdpPayloadQuoteReplaceMessageShortForm::operator!=(const UdpPayloadQuoteReplaceMessageShortForm& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
