#include "SingleSideReplaceMessageShortForm.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

SingleSideReplaceMessageShortForm::SingleSideReplaceMessageShortForm(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t original_reference_number, std::uint64_t new_reference_number, Decimal price_short, std::uint16_t volume_short)
  : tracking_number_(tracking_number), timestamp_(timestamp), original_reference_number_(original_reference_number), new_reference_number_(new_reference_number), price_short_(price_short), volume_short_(volume_short) {}

std::uint16_t SingleSideReplaceMessageShortForm::tracking_number() const { return tracking_number_; }
void SingleSideReplaceMessageShortForm::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds SingleSideReplaceMessageShortForm::timestamp() const { return timestamp_; }
void SingleSideReplaceMessageShortForm::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t SingleSideReplaceMessageShortForm::original_reference_number() const { return original_reference_number_; }
void SingleSideReplaceMessageShortForm::set_original_reference_number(std::uint64_t value) { original_reference_number_ = value; }

std::uint64_t SingleSideReplaceMessageShortForm::new_reference_number() const { return new_reference_number_; }
void SingleSideReplaceMessageShortForm::set_new_reference_number(std::uint64_t value) { new_reference_number_ = value; }

Decimal SingleSideReplaceMessageShortForm::price_short() const { return price_short_; }
void SingleSideReplaceMessageShortForm::set_price_short(Decimal value) { price_short_ = value; }

std::uint16_t SingleSideReplaceMessageShortForm::volume_short() const { return volume_short_; }
void SingleSideReplaceMessageShortForm::set_volume_short(std::uint16_t value) { volume_short_ = value; }

SequencedMessageCode SingleSideReplaceMessageShortForm::type() const { return message_type; }

std::string_view SingleSideReplaceMessageShortForm::name() const { return "Single Side Replace Message Short Form"; }

std::size_t SingleSideReplaceMessageShortForm::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SingleSideReplaceMessageShortForm", wire_size, length);

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

std::size_t SingleSideReplaceMessageShortForm::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SingleSideReplaceMessageShortForm", wire_size, capacity);

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

std::size_t SingleSideReplaceMessageShortForm::encoded_size() const {
    return wire_size;
}

void SingleSideReplaceMessageShortForm::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> SingleSideReplaceMessageShortForm::clone() const {
    return std::make_unique<SingleSideReplaceMessageShortForm>(*this);
}

void SingleSideReplaceMessageShortForm::print(std::ostream& out) const {
    out << "SingleSideReplaceMessageShortForm{";
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

bool SingleSideReplaceMessageShortForm::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const SingleSideReplaceMessageShortForm*>(&other);
    return that != nullptr && *this == *that;
}

bool SingleSideReplaceMessageShortForm::operator==(const SingleSideReplaceMessageShortForm& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && original_reference_number_ == other.original_reference_number_
        && new_reference_number_ == other.new_reference_number_
        && price_short_ == other.price_short_
        && volume_short_ == other.volume_short_;
}

bool SingleSideReplaceMessageShortForm::operator!=(const SingleSideReplaceMessageShortForm& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
