#include "StrikePrice.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

StrikePrice::StrikePrice(std::int8_t strike_price_exponent, std::int32_t strike_price_mantissa)
  : strike_price_exponent_(strike_price_exponent), strike_price_mantissa_(strike_price_mantissa) {}

std::int8_t StrikePrice::strike_price_exponent() const { return strike_price_exponent_; }
void StrikePrice::set_strike_price_exponent(std::int8_t value) { strike_price_exponent_ = value; }

std::int32_t StrikePrice::strike_price_mantissa() const { return strike_price_mantissa_; }
void StrikePrice::set_strike_price_mantissa(std::int32_t value) { strike_price_mantissa_ = value; }

std::size_t StrikePrice::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StrikePrice", wire_size, length);

    strike_price_exponent_ = wire::read_i8(data + offset);
    offset += 1;

    strike_price_mantissa_ = wire::read_i32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t StrikePrice::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StrikePrice", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(strike_price_exponent_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(strike_price_mantissa_));
    offset += 4;

    return offset;
}

std::size_t StrikePrice::encoded_size() const {
    return wire_size;
}

void StrikePrice::print(std::ostream& out) const {
    out << "StrikePrice{";
    out << "strike_price_exponent=";
    out << static_cast<int>(strike_price_exponent_);
    out << ", strike_price_mantissa=";
    out << strike_price_mantissa_;
    out << '}';
}

bool StrikePrice::operator==(const StrikePrice& other) const {
    return strike_price_exponent_ == other.strike_price_exponent_
        && strike_price_mantissa_ == other.strike_price_mantissa_;
}

bool StrikePrice::operator!=(const StrikePrice& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const StrikePrice& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
