#include "SingleSideExecutedWithPriceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

SingleSideExecutedWithPriceMessage::SingleSideExecutedWithPriceMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t reference_number, std::uint32_t cross_number, std::uint32_t match_number, Printable printable, Decimal price_long, std::uint32_t volume_long)
  : tracking_number_(tracking_number), timestamp_(timestamp), reference_number_(reference_number), cross_number_(cross_number), match_number_(match_number), printable_(printable), price_long_(price_long), volume_long_(volume_long) {}

std::uint16_t SingleSideExecutedWithPriceMessage::tracking_number() const { return tracking_number_; }
void SingleSideExecutedWithPriceMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds SingleSideExecutedWithPriceMessage::timestamp() const { return timestamp_; }
void SingleSideExecutedWithPriceMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t SingleSideExecutedWithPriceMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint64_t SingleSideExecutedWithPriceMessage::reference_number() const { return reference_number_; }
void SingleSideExecutedWithPriceMessage::set_reference_number(std::uint64_t value) { reference_number_ = value; }

std::uint32_t SingleSideExecutedWithPriceMessage::cross_number() const { return cross_number_; }
void SingleSideExecutedWithPriceMessage::set_cross_number(std::uint32_t value) { cross_number_ = value; }

std::uint32_t SingleSideExecutedWithPriceMessage::match_number() const { return match_number_; }
void SingleSideExecutedWithPriceMessage::set_match_number(std::uint32_t value) { match_number_ = value; }

Printable SingleSideExecutedWithPriceMessage::printable() const { return printable_; }
void SingleSideExecutedWithPriceMessage::set_printable(Printable value) { printable_ = value; }

Decimal SingleSideExecutedWithPriceMessage::price_long() const { return price_long_; }
void SingleSideExecutedWithPriceMessage::set_price_long(Decimal value) { price_long_ = value; }

std::uint32_t SingleSideExecutedWithPriceMessage::volume_long() const { return volume_long_; }
void SingleSideExecutedWithPriceMessage::set_volume_long(std::uint32_t value) { volume_long_ = value; }

SequencedMessageCode SingleSideExecutedWithPriceMessage::type() const { return message_type; }

std::string_view SingleSideExecutedWithPriceMessage::name() const { return "Single Side Executed With Price Message"; }

std::size_t SingleSideExecutedWithPriceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SingleSideExecutedWithPriceMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    cross_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    match_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    printable_ = static_cast<Printable>(wire::read_char(data + offset));
    offset += 1;

    price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    volume_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t SingleSideExecutedWithPriceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SingleSideExecutedWithPriceMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(cross_number_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(match_number_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(printable_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_long_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(volume_long_));
    offset += 4;

    return offset;
}

std::size_t SingleSideExecutedWithPriceMessage::encoded_size() const {
    return wire_size;
}

void SingleSideExecutedWithPriceMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> SingleSideExecutedWithPriceMessage::clone() const {
    return std::make_unique<SingleSideExecutedWithPriceMessage>(*this);
}

void SingleSideExecutedWithPriceMessage::print(std::ostream& out) const {
    out << "SingleSideExecutedWithPriceMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", reference_number=";
    out << reference_number_;
    out << ", cross_number=";
    out << cross_number_;
    out << ", match_number=";
    out << match_number_;
    out << ", printable=";
    out << printable_;
    out << ", price_long=";
    out << price_long_;
    out << ", volume_long=";
    out << volume_long_;
    out << '}';
}

bool SingleSideExecutedWithPriceMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const SingleSideExecutedWithPriceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SingleSideExecutedWithPriceMessage::operator==(const SingleSideExecutedWithPriceMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && reference_number_ == other.reference_number_
        && cross_number_ == other.cross_number_
        && match_number_ == other.match_number_
        && printable_ == other.printable_
        && price_long_ == other.price_long_
        && volume_long_ == other.volume_long_;
}

bool SingleSideExecutedWithPriceMessage::operator!=(const SingleSideExecutedWithPriceMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
