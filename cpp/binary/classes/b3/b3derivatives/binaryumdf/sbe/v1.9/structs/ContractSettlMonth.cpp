#include "ContractSettlMonth.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

ContractSettlMonth::ContractSettlMonth(std::uint16_t year, std::uint8_t month, std::uint8_t day, std::uint8_t week)
  : year_(year), month_(month), day_(day), week_(week) {}

std::uint16_t ContractSettlMonth::year() const { return year_; }
void ContractSettlMonth::set_year(std::uint16_t value) { year_ = value; }

std::uint8_t ContractSettlMonth::month() const { return month_; }
void ContractSettlMonth::set_month(std::uint8_t value) { month_ = value; }

std::uint8_t ContractSettlMonth::day() const { return day_; }
void ContractSettlMonth::set_day(std::uint8_t value) { day_ = value; }

std::uint8_t ContractSettlMonth::week() const { return week_; }
void ContractSettlMonth::set_week(std::uint8_t value) { week_ = value; }

std::size_t ContractSettlMonth::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ContractSettlMonth", wire_size, length);

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

std::size_t ContractSettlMonth::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ContractSettlMonth", wire_size, capacity);

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

std::size_t ContractSettlMonth::encoded_size() const {
    return wire_size;
}

void ContractSettlMonth::print(std::ostream& out) const {
    out << "ContractSettlMonth{";
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

bool ContractSettlMonth::operator==(const ContractSettlMonth& other) const {
    return year_ == other.year_
        && month_ == other.month_
        && day_ == other.day_
        && week_ == other.week_;
}

bool ContractSettlMonth::operator!=(const ContractSettlMonth& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ContractSettlMonth& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
