#include "MwcbDeclineLevelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

MwcbDeclineLevelMessage::MwcbDeclineLevelMessage(std::uint16_t tracking_number, std::chrono::nanoseconds time_stamp, Decimal level_1, Decimal level_2, Decimal level_3)
  : tracking_number_(tracking_number), time_stamp_(time_stamp), level_1_(level_1), level_2_(level_2), level_3_(level_3) {}

std::uint16_t MwcbDeclineLevelMessage::tracking_number() const { return tracking_number_; }
void MwcbDeclineLevelMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds MwcbDeclineLevelMessage::time_stamp() const { return time_stamp_; }
void MwcbDeclineLevelMessage::set_time_stamp(std::chrono::nanoseconds value) { time_stamp_ = value; }
std::int64_t MwcbDeclineLevelMessage::time_stamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(time_stamp_.count())); }

Decimal MwcbDeclineLevelMessage::level_1() const { return level_1_; }
void MwcbDeclineLevelMessage::set_level_1(Decimal value) { level_1_ = value; }

Decimal MwcbDeclineLevelMessage::level_2() const { return level_2_; }
void MwcbDeclineLevelMessage::set_level_2(Decimal value) { level_2_ = value; }

Decimal MwcbDeclineLevelMessage::level_3() const { return level_3_; }
void MwcbDeclineLevelMessage::set_level_3(Decimal value) { level_3_ = value; }

MessageCode MwcbDeclineLevelMessage::type() const { return message_type; }

std::string_view MwcbDeclineLevelMessage::name() const { return "Mwcb Decline Level Message"; }

std::size_t MwcbDeclineLevelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MwcbDeclineLevelMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    time_stamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    level_1_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -8);
    offset += 8;

    level_2_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -8);
    offset += 8;

    level_3_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -8);
    offset += 8;

    return offset;
}

std::size_t MwcbDeclineLevelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MwcbDeclineLevelMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(time_stamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(level_1_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(level_2_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(level_3_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t MwcbDeclineLevelMessage::encoded_size() const {
    return wire_size;
}

void MwcbDeclineLevelMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MwcbDeclineLevelMessage::clone() const {
    return std::make_unique<MwcbDeclineLevelMessage>(*this);
}

void MwcbDeclineLevelMessage::print(std::ostream& out) const {
    out << "MwcbDeclineLevelMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", time_stamp=";
    calendar::print(out, time_stamp_.count(), 1, "America/New_York");
    out << ", level_1=";
    out << level_1_;
    out << ", level_2=";
    out << level_2_;
    out << ", level_3=";
    out << level_3_;
    out << '}';
}

bool MwcbDeclineLevelMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MwcbDeclineLevelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MwcbDeclineLevelMessage::operator==(const MwcbDeclineLevelMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && time_stamp_ == other.time_stamp_
        && level_1_ == other.level_1_
        && level_2_ == other.level_2_
        && level_3_ == other.level_3_;
}

bool MwcbDeclineLevelMessage::operator!=(const MwcbDeclineLevelMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
