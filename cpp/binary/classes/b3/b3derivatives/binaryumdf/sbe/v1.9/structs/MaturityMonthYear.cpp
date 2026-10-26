#include "MaturityMonthYear.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

MaturityMonthYear::MaturityMonthYear(std::uint16_t year, std::uint8_t month, std::uint8_t day, std::uint8_t week)
  : year_(year), month_(month), day_(day), week_(week) {}

std::uint16_t MaturityMonthYear::year() const { return year_; }
void MaturityMonthYear::set_year(std::uint16_t value) { year_ = value; }

std::uint8_t MaturityMonthYear::month() const { return month_; }
void MaturityMonthYear::set_month(std::uint8_t value) { month_ = value; }

std::uint8_t MaturityMonthYear::day() const { return day_; }
void MaturityMonthYear::set_day(std::uint8_t value) { day_ = value; }

std::uint8_t MaturityMonthYear::week() const { return week_; }
void MaturityMonthYear::set_week(std::uint8_t value) { week_ = value; }

std::size_t MaturityMonthYear::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MaturityMonthYear", wire_size, length);

    year_ = wire::read_u16_le(data + offset);
    offset += 2;

    month_ = wire::read_u8(data + offset);
    offset += 1;

    day_ = wire::read_u8(data + offset);
    offset += 1;

    week_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t MaturityMonthYear::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MaturityMonthYear", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(year_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(month_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(day_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(week_));
    offset += 1;

    return offset;
}

std::size_t MaturityMonthYear::encoded_size() const {
    return wire_size;
}

void MaturityMonthYear::print(std::ostream& out) const {
    out << "MaturityMonthYear{";
    out << "year=";
    out << year_;
    out << ", month=";
    out << static_cast<int>(month_);
    out << ", day=";
    out << static_cast<int>(day_);
    out << ", week=";
    out << static_cast<int>(week_);
    out << '}';
}

bool MaturityMonthYear::operator==(const MaturityMonthYear& other) const {
    return year_ == other.year_
        && month_ == other.month_
        && day_ == other.day_
        && week_ == other.week_;
}

bool MaturityMonthYear::operator!=(const MaturityMonthYear& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MaturityMonthYear& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
