#include "MinimumBelowPremiumFraction.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

MinimumBelowPremiumFraction::MinimumBelowPremiumFraction(std::int8_t minimum_below_premium_fraction_exponent, std::int32_t minimum_below_premium_fraction_mantissa)
  : minimum_below_premium_fraction_exponent_(minimum_below_premium_fraction_exponent), minimum_below_premium_fraction_mantissa_(minimum_below_premium_fraction_mantissa) {}

std::int8_t MinimumBelowPremiumFraction::minimum_below_premium_fraction_exponent() const { return minimum_below_premium_fraction_exponent_; }
void MinimumBelowPremiumFraction::set_minimum_below_premium_fraction_exponent(std::int8_t value) { minimum_below_premium_fraction_exponent_ = value; }

std::int32_t MinimumBelowPremiumFraction::minimum_below_premium_fraction_mantissa() const { return minimum_below_premium_fraction_mantissa_; }
void MinimumBelowPremiumFraction::set_minimum_below_premium_fraction_mantissa(std::int32_t value) { minimum_below_premium_fraction_mantissa_ = value; }

std::size_t MinimumBelowPremiumFraction::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MinimumBelowPremiumFraction", wire_size, length);

    minimum_below_premium_fraction_exponent_ = wire::read_i8(data + offset);
    offset += 1;

    minimum_below_premium_fraction_mantissa_ = wire::read_i32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t MinimumBelowPremiumFraction::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MinimumBelowPremiumFraction", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(minimum_below_premium_fraction_exponent_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(minimum_below_premium_fraction_mantissa_));
    offset += 4;

    return offset;
}

std::size_t MinimumBelowPremiumFraction::encoded_size() const {
    return wire_size;
}

void MinimumBelowPremiumFraction::print(std::ostream& out) const {
    out << "MinimumBelowPremiumFraction{";
    out << "minimum_below_premium_fraction_exponent=";
    out << static_cast<int>(minimum_below_premium_fraction_exponent_);
    out << ", minimum_below_premium_fraction_mantissa=";
    out << minimum_below_premium_fraction_mantissa_;
    out << '}';
}

bool MinimumBelowPremiumFraction::operator==(const MinimumBelowPremiumFraction& other) const {
    return minimum_below_premium_fraction_exponent_ == other.minimum_below_premium_fraction_exponent_
        && minimum_below_premium_fraction_mantissa_ == other.minimum_below_premium_fraction_mantissa_;
}

bool MinimumBelowPremiumFraction::operator!=(const MinimumBelowPremiumFraction& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MinimumBelowPremiumFraction& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
