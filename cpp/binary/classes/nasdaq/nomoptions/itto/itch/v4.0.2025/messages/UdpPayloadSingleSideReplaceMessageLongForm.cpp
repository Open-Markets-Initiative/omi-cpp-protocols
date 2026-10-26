#include "UdpPayloadSingleSideReplaceMessageLongForm.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadSingleSideReplaceMessageLongForm::UdpPayloadSingleSideReplaceMessageLongForm(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t original_reference_number, std::uint64_t new_reference_number, Decimal price_long, std::uint32_t volume_long)
  : tracking_number_(tracking_number), timestamp_(timestamp), original_reference_number_(original_reference_number), new_reference_number_(new_reference_number), price_long_(price_long), volume_long_(volume_long) {}

std::uint16_t UdpPayloadSingleSideReplaceMessageLongForm::tracking_number() const { return tracking_number_; }
void UdpPayloadSingleSideReplaceMessageLongForm::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadSingleSideReplaceMessageLongForm::timestamp() const { return timestamp_; }
void UdpPayloadSingleSideReplaceMessageLongForm::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t UdpPayloadSingleSideReplaceMessageLongForm::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint64_t UdpPayloadSingleSideReplaceMessageLongForm::original_reference_number() const { return original_reference_number_; }
void UdpPayloadSingleSideReplaceMessageLongForm::set_original_reference_number(std::uint64_t value) { original_reference_number_ = value; }

std::uint64_t UdpPayloadSingleSideReplaceMessageLongForm::new_reference_number() const { return new_reference_number_; }
void UdpPayloadSingleSideReplaceMessageLongForm::set_new_reference_number(std::uint64_t value) { new_reference_number_ = value; }

Decimal UdpPayloadSingleSideReplaceMessageLongForm::price_long() const { return price_long_; }
void UdpPayloadSingleSideReplaceMessageLongForm::set_price_long(Decimal value) { price_long_ = value; }

std::uint32_t UdpPayloadSingleSideReplaceMessageLongForm::volume_long() const { return volume_long_; }
void UdpPayloadSingleSideReplaceMessageLongForm::set_volume_long(std::uint32_t value) { volume_long_ = value; }

PacketMessageCode UdpPayloadSingleSideReplaceMessageLongForm::type() const { return message_type; }

std::string_view UdpPayloadSingleSideReplaceMessageLongForm::name() const { return "Single Side Replace Message Long Form"; }

std::size_t UdpPayloadSingleSideReplaceMessageLongForm::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadSingleSideReplaceMessageLongForm", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    original_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    new_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    volume_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t UdpPayloadSingleSideReplaceMessageLongForm::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadSingleSideReplaceMessageLongForm", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(original_reference_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(new_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_long_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(volume_long_));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadSingleSideReplaceMessageLongForm::encoded_size() const {
    return wire_size;
}

void UdpPayloadSingleSideReplaceMessageLongForm::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadSingleSideReplaceMessageLongForm::clone() const {
    return std::make_unique<UdpPayloadSingleSideReplaceMessageLongForm>(*this);
}

void UdpPayloadSingleSideReplaceMessageLongForm::print(std::ostream& out) const {
    out << "UdpPayloadSingleSideReplaceMessageLongForm{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", original_reference_number=";
    out << original_reference_number_;
    out << ", new_reference_number=";
    out << new_reference_number_;
    out << ", price_long=";
    out << price_long_;
    out << ", volume_long=";
    out << volume_long_;
    out << '}';
}

bool UdpPayloadSingleSideReplaceMessageLongForm::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadSingleSideReplaceMessageLongForm*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadSingleSideReplaceMessageLongForm::operator==(const UdpPayloadSingleSideReplaceMessageLongForm& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && original_reference_number_ == other.original_reference_number_
        && new_reference_number_ == other.new_reference_number_
        && price_long_ == other.price_long_
        && volume_long_ == other.volume_long_;
}

bool UdpPayloadSingleSideReplaceMessageLongForm::operator!=(const UdpPayloadSingleSideReplaceMessageLongForm& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
