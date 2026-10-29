#include "PremiumBreakPoint.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

PremiumBreakPoint::PremiumBreakPoint(std::int8_t premium_break_point_exponent, std::int32_t premium_break_point_mantissa)
  : premium_break_point_exponent_(premium_break_point_exponent), premium_break_point_mantissa_(premium_break_point_mantissa) {}

std::int8_t PremiumBreakPoint::premium_break_point_exponent() const { return premium_break_point_exponent_; }
void PremiumBreakPoint::set_premium_break_point_exponent(std::int8_t value) { premium_break_point_exponent_ = value; }

std::int32_t PremiumBreakPoint::premium_break_point_mantissa() const { return premium_break_point_mantissa_; }
void PremiumBreakPoint::set_premium_break_point_mantissa(std::int32_t value) { premium_break_point_mantissa_ = value; }

std::size_t PremiumBreakPoint::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PremiumBreakPoint", wire_size, length);

    premium_break_point_exponent_ = wire::read_i8(data + offset);
    offset += 1;

    premium_break_point_mantissa_ = wire::read_i32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t PremiumBreakPoint::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PremiumBreakPoint", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(premium_break_point_exponent_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(premium_break_point_mantissa_));
    offset += 4;

    return offset;
}

std::size_t PremiumBreakPoint::encoded_size() const {
    return wire_size;
}

void PremiumBreakPoint::print(std::ostream& out) const {
    out << "PremiumBreakPoint{";
    out << "premium_break_point_exponent=";
    out << static_cast<int>(premium_break_point_exponent_);
    out << ", premium_break_point_mantissa=";
    out << premium_break_point_mantissa_;
    out << '}';
}

bool PremiumBreakPoint::operator==(const PremiumBreakPoint& other) const {
    return premium_break_point_exponent_ == other.premium_break_point_exponent_
        && premium_break_point_mantissa_ == other.premium_break_point_mantissa_;
}

bool PremiumBreakPoint::operator!=(const PremiumBreakPoint& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PremiumBreakPoint& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
