#include "MinimumAbovePremiumFraction.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

MinimumAbovePremiumFraction::MinimumAbovePremiumFraction(std::int8_t minimum_above_premium_fraction_exponent, std::int32_t minimum_above_premium_fraction_mantissa)
  : minimum_above_premium_fraction_exponent_(minimum_above_premium_fraction_exponent), minimum_above_premium_fraction_mantissa_(minimum_above_premium_fraction_mantissa) {}

std::int8_t MinimumAbovePremiumFraction::minimum_above_premium_fraction_exponent() const { return minimum_above_premium_fraction_exponent_; }
void MinimumAbovePremiumFraction::set_minimum_above_premium_fraction_exponent(std::int8_t value) { minimum_above_premium_fraction_exponent_ = value; }

std::int32_t MinimumAbovePremiumFraction::minimum_above_premium_fraction_mantissa() const { return minimum_above_premium_fraction_mantissa_; }
void MinimumAbovePremiumFraction::set_minimum_above_premium_fraction_mantissa(std::int32_t value) { minimum_above_premium_fraction_mantissa_ = value; }

std::size_t MinimumAbovePremiumFraction::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MinimumAbovePremiumFraction", wire_size, length);

    minimum_above_premium_fraction_exponent_ = wire::read_i8(data + offset);
    offset += 1;

    minimum_above_premium_fraction_mantissa_ = wire::read_i32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t MinimumAbovePremiumFraction::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MinimumAbovePremiumFraction", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(minimum_above_premium_fraction_exponent_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(minimum_above_premium_fraction_mantissa_));
    offset += 4;

    return offset;
}

std::size_t MinimumAbovePremiumFraction::encoded_size() const {
    return wire_size;
}

void MinimumAbovePremiumFraction::print(std::ostream& out) const {
    out << "MinimumAbovePremiumFraction{";
    out << "minimum_above_premium_fraction_exponent=";
    out << static_cast<int>(minimum_above_premium_fraction_exponent_);
    out << ", minimum_above_premium_fraction_mantissa=";
    out << minimum_above_premium_fraction_mantissa_;
    out << '}';
}

bool MinimumAbovePremiumFraction::operator==(const MinimumAbovePremiumFraction& other) const {
    return minimum_above_premium_fraction_exponent_ == other.minimum_above_premium_fraction_exponent_
        && minimum_above_premium_fraction_mantissa_ == other.minimum_above_premium_fraction_mantissa_;
}

bool MinimumAbovePremiumFraction::operator!=(const MinimumAbovePremiumFraction& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MinimumAbovePremiumFraction& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
