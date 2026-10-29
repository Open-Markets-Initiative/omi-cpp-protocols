#include "MaxStrikePrice.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

MaxStrikePrice::MaxStrikePrice(std::int8_t max_strike_price_exponent, std::int32_t max_strike_price_mantissa)
  : max_strike_price_exponent_(max_strike_price_exponent), max_strike_price_mantissa_(max_strike_price_mantissa) {}

std::int8_t MaxStrikePrice::max_strike_price_exponent() const { return max_strike_price_exponent_; }
void MaxStrikePrice::set_max_strike_price_exponent(std::int8_t value) { max_strike_price_exponent_ = value; }

std::int32_t MaxStrikePrice::max_strike_price_mantissa() const { return max_strike_price_mantissa_; }
void MaxStrikePrice::set_max_strike_price_mantissa(std::int32_t value) { max_strike_price_mantissa_ = value; }

std::size_t MaxStrikePrice::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MaxStrikePrice", wire_size, length);

    max_strike_price_exponent_ = wire::read_i8(data + offset);
    offset += 1;

    max_strike_price_mantissa_ = wire::read_i32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t MaxStrikePrice::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MaxStrikePrice", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(max_strike_price_exponent_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(max_strike_price_mantissa_));
    offset += 4;

    return offset;
}

std::size_t MaxStrikePrice::encoded_size() const {
    return wire_size;
}

void MaxStrikePrice::print(std::ostream& out) const {
    out << "MaxStrikePrice{";
    out << "max_strike_price_exponent=";
    out << static_cast<int>(max_strike_price_exponent_);
    out << ", max_strike_price_mantissa=";
    out << max_strike_price_mantissa_;
    out << '}';
}

bool MaxStrikePrice::operator==(const MaxStrikePrice& other) const {
    return max_strike_price_exponent_ == other.max_strike_price_exponent_
        && max_strike_price_mantissa_ == other.max_strike_price_mantissa_;
}

bool MaxStrikePrice::operator!=(const MaxStrikePrice& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MaxStrikePrice& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
