#include "UdpPayloadSingleSideReplaceMessageShortForm.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadSingleSideReplaceMessageShortForm::UdpPayloadSingleSideReplaceMessageShortForm(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t original_reference_number, std::uint64_t new_reference_number, Decimal price_short, std::uint16_t volume_short)
  : tracking_number_(tracking_number), timestamp_(timestamp), original_reference_number_(original_reference_number), new_reference_number_(new_reference_number), price_short_(price_short), volume_short_(volume_short) {}

std::uint16_t UdpPayloadSingleSideReplaceMessageShortForm::tracking_number() const { return tracking_number_; }
void UdpPayloadSingleSideReplaceMessageShortForm::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadSingleSideReplaceMessageShortForm::timestamp() const { return timestamp_; }
void UdpPayloadSingleSideReplaceMessageShortForm::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t UdpPayloadSingleSideReplaceMessageShortForm::original_reference_number() const { return original_reference_number_; }
void UdpPayloadSingleSideReplaceMessageShortForm::set_original_reference_number(std::uint64_t value) { original_reference_number_ = value; }

std::uint64_t UdpPayloadSingleSideReplaceMessageShortForm::new_reference_number() const { return new_reference_number_; }
void UdpPayloadSingleSideReplaceMessageShortForm::set_new_reference_number(std::uint64_t value) { new_reference_number_ = value; }

Decimal UdpPayloadSingleSideReplaceMessageShortForm::price_short() const { return price_short_; }
void UdpPayloadSingleSideReplaceMessageShortForm::set_price_short(Decimal value) { price_short_ = value; }

std::uint16_t UdpPayloadSingleSideReplaceMessageShortForm::volume_short() const { return volume_short_; }
void UdpPayloadSingleSideReplaceMessageShortForm::set_volume_short(std::uint16_t value) { volume_short_ = value; }

PacketMessageCode UdpPayloadSingleSideReplaceMessageShortForm::type() const { return message_type; }

std::string_view UdpPayloadSingleSideReplaceMessageShortForm::name() const { return "Single Side Replace Message Short Form"; }

std::size_t UdpPayloadSingleSideReplaceMessageShortForm::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadSingleSideReplaceMessageShortForm", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    original_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    new_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -4);
    offset += 2;

    volume_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t UdpPayloadSingleSideReplaceMessageShortForm::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadSingleSideReplaceMessageShortForm", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(original_reference_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(new_reference_number_));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(volume_short_));
    offset += 2;

    return offset;
}

std::size_t UdpPayloadSingleSideReplaceMessageShortForm::encoded_size() const {
    return wire_size;
}

void UdpPayloadSingleSideReplaceMessageShortForm::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadSingleSideReplaceMessageShortForm::clone() const {
    return std::make_unique<UdpPayloadSingleSideReplaceMessageShortForm>(*this);
}

void UdpPayloadSingleSideReplaceMessageShortForm::print(std::ostream& out) const {
    out << "UdpPayloadSingleSideReplaceMessageShortForm{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", original_reference_number=";
    out << original_reference_number_;
    out << ", new_reference_number=";
    out << new_reference_number_;
    out << ", price_short=";
    out << price_short_;
    out << ", volume_short=";
    out << volume_short_;
    out << '}';
}

bool UdpPayloadSingleSideReplaceMessageShortForm::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadSingleSideReplaceMessageShortForm*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadSingleSideReplaceMessageShortForm::operator==(const UdpPayloadSingleSideReplaceMessageShortForm& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && original_reference_number_ == other.original_reference_number_
        && new_reference_number_ == other.new_reference_number_
        && price_short_ == other.price_short_
        && volume_short_ == other.volume_short_;
}

bool UdpPayloadSingleSideReplaceMessageShortForm::operator!=(const UdpPayloadSingleSideReplaceMessageShortForm& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
