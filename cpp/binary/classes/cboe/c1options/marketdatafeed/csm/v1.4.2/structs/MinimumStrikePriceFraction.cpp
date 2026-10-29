#include "MinimumStrikePriceFraction.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

MinimumStrikePriceFraction::MinimumStrikePriceFraction(std::int8_t minimum_strike_price_fraction_exponent, std::int32_t minimum_strike_price_fraction_mantissa)
  : minimum_strike_price_fraction_exponent_(minimum_strike_price_fraction_exponent), minimum_strike_price_fraction_mantissa_(minimum_strike_price_fraction_mantissa) {}

std::int8_t MinimumStrikePriceFraction::minimum_strike_price_fraction_exponent() const { return minimum_strike_price_fraction_exponent_; }
void MinimumStrikePriceFraction::set_minimum_strike_price_fraction_exponent(std::int8_t value) { minimum_strike_price_fraction_exponent_ = value; }

std::int32_t MinimumStrikePriceFraction::minimum_strike_price_fraction_mantissa() const { return minimum_strike_price_fraction_mantissa_; }
void MinimumStrikePriceFraction::set_minimum_strike_price_fraction_mantissa(std::int32_t value) { minimum_strike_price_fraction_mantissa_ = value; }

std::size_t MinimumStrikePriceFraction::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MinimumStrikePriceFraction", wire_size, length);

    minimum_strike_price_fraction_exponent_ = wire::read_i8(data + offset);
    offset += 1;

    minimum_strike_price_fraction_mantissa_ = wire::read_i32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t MinimumStrikePriceFraction::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MinimumStrikePriceFraction", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(minimum_strike_price_fraction_exponent_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(minimum_strike_price_fraction_mantissa_));
    offset += 4;

    return offset;
}

std::size_t MinimumStrikePriceFraction::encoded_size() const {
    return wire_size;
}

void MinimumStrikePriceFraction::print(std::ostream& out) const {
    out << "MinimumStrikePriceFraction{";
    out << "minimum_strike_price_fraction_exponent=";
    out << static_cast<int>(minimum_strike_price_fraction_exponent_);
    out << ", minimum_strike_price_fraction_mantissa=";
    out << minimum_strike_price_fraction_mantissa_;
    out << '}';
}

bool MinimumStrikePriceFraction::operator==(const MinimumStrikePriceFraction& other) const {
    return minimum_strike_price_fraction_exponent_ == other.minimum_strike_price_fraction_exponent_
        && minimum_strike_price_fraction_mantissa_ == other.minimum_strike_price_fraction_mantissa_;
}

bool MinimumStrikePriceFraction::operator!=(const MinimumStrikePriceFraction& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MinimumStrikePriceFraction& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
