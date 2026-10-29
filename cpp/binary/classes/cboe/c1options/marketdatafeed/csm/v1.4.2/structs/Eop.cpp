#include "Eop.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

Eop::Eop(std::int8_t eop_exponent, std::int32_t eop_mantissa)
  : eop_exponent_(eop_exponent), eop_mantissa_(eop_mantissa) {}

std::int8_t Eop::eop_exponent() const { return eop_exponent_; }
void Eop::set_eop_exponent(std::int8_t value) { eop_exponent_ = value; }

std::int32_t Eop::eop_mantissa() const { return eop_mantissa_; }
void Eop::set_eop_mantissa(std::int32_t value) { eop_mantissa_ = value; }

std::size_t Eop::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("Eop", wire_size, length);

    eop_exponent_ = wire::read_i8(data + offset);
    offset += 1;

    eop_mantissa_ = wire::read_i32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t Eop::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Eop", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(eop_exponent_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(eop_mantissa_));
    offset += 4;

    return offset;
}

std::size_t Eop::encoded_size() const {
    return wire_size;
}

void Eop::print(std::ostream& out) const {
    out << "Eop{";
    out << "eop_exponent=";
    out << static_cast<int>(eop_exponent_);
    out << ", eop_mantissa=";
    out << eop_mantissa_;
    out << '}';
}

bool Eop::operator==(const Eop& other) const {
    return eop_exponent_ == other.eop_exponent_
        && eop_mantissa_ == other.eop_mantissa_;
}

bool Eop::operator!=(const Eop& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Eop& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
