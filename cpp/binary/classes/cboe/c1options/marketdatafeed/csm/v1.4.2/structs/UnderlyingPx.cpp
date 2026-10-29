#include "UnderlyingPx.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

UnderlyingPx::UnderlyingPx(std::int8_t underlying_px_exponent, std::int32_t underlying_px_mantissa)
  : underlying_px_exponent_(underlying_px_exponent), underlying_px_mantissa_(underlying_px_mantissa) {}

std::int8_t UnderlyingPx::underlying_px_exponent() const { return underlying_px_exponent_; }
void UnderlyingPx::set_underlying_px_exponent(std::int8_t value) { underlying_px_exponent_ = value; }

std::int32_t UnderlyingPx::underlying_px_mantissa() const { return underlying_px_mantissa_; }
void UnderlyingPx::set_underlying_px_mantissa(std::int32_t value) { underlying_px_mantissa_ = value; }

std::size_t UnderlyingPx::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UnderlyingPx", wire_size, length);

    underlying_px_exponent_ = wire::read_i8(data + offset);
    offset += 1;

    underlying_px_mantissa_ = wire::read_i32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t UnderlyingPx::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnderlyingPx", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(underlying_px_exponent_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(underlying_px_mantissa_));
    offset += 4;

    return offset;
}

std::size_t UnderlyingPx::encoded_size() const {
    return wire_size;
}

void UnderlyingPx::print(std::ostream& out) const {
    out << "UnderlyingPx{";
    out << "underlying_px_exponent=";
    out << static_cast<int>(underlying_px_exponent_);
    out << ", underlying_px_mantissa=";
    out << underlying_px_mantissa_;
    out << '}';
}

bool UnderlyingPx::operator==(const UnderlyingPx& other) const {
    return underlying_px_exponent_ == other.underlying_px_exponent_
        && underlying_px_mantissa_ == other.underlying_px_mantissa_;
}

bool UnderlyingPx::operator!=(const UnderlyingPx& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const UnderlyingPx& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
