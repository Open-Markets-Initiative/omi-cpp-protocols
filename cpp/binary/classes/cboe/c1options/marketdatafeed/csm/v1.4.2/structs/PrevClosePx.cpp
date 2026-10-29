#include "PrevClosePx.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

PrevClosePx::PrevClosePx(std::int8_t prev_close_px_exponent, std::int32_t prev_close_px_mantissa)
  : prev_close_px_exponent_(prev_close_px_exponent), prev_close_px_mantissa_(prev_close_px_mantissa) {}

std::int8_t PrevClosePx::prev_close_px_exponent() const { return prev_close_px_exponent_; }
void PrevClosePx::set_prev_close_px_exponent(std::int8_t value) { prev_close_px_exponent_ = value; }

std::int32_t PrevClosePx::prev_close_px_mantissa() const { return prev_close_px_mantissa_; }
void PrevClosePx::set_prev_close_px_mantissa(std::int32_t value) { prev_close_px_mantissa_ = value; }

std::size_t PrevClosePx::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PrevClosePx", wire_size, length);

    prev_close_px_exponent_ = wire::read_i8(data + offset);
    offset += 1;

    prev_close_px_mantissa_ = wire::read_i32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t PrevClosePx::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PrevClosePx", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(prev_close_px_exponent_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(prev_close_px_mantissa_));
    offset += 4;

    return offset;
}

std::size_t PrevClosePx::encoded_size() const {
    return wire_size;
}

void PrevClosePx::print(std::ostream& out) const {
    out << "PrevClosePx{";
    out << "prev_close_px_exponent=";
    out << static_cast<int>(prev_close_px_exponent_);
    out << ", prev_close_px_mantissa=";
    out << prev_close_px_mantissa_;
    out << '}';
}

bool PrevClosePx::operator==(const PrevClosePx& other) const {
    return prev_close_px_exponent_ == other.prev_close_px_exponent_
        && prev_close_px_mantissa_ == other.prev_close_px_mantissa_;
}

bool PrevClosePx::operator!=(const PrevClosePx& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PrevClosePx& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
