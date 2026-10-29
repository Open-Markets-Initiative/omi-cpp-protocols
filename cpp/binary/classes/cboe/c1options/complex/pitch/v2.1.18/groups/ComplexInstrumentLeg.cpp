#include "ComplexInstrumentLeg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

ComplexInstrumentLeg::ComplexInstrumentLeg(const std::string& leg_symbol, std::int32_t leg_ratio, LegSecurityType leg_security_type)
  : leg_symbol_(leg_symbol), leg_ratio_(leg_ratio), leg_security_type_(leg_security_type) {}

const std::string& ComplexInstrumentLeg::leg_symbol() const { return leg_symbol_; }
std::string& ComplexInstrumentLeg::leg_symbol() { return leg_symbol_; }
void ComplexInstrumentLeg::set_leg_symbol(const std::string& value) { leg_symbol_ = value; }

std::int32_t ComplexInstrumentLeg::leg_ratio() const { return leg_ratio_; }
void ComplexInstrumentLeg::set_leg_ratio(std::int32_t value) { leg_ratio_ = value; }

LegSecurityType ComplexInstrumentLeg::leg_security_type() const { return leg_security_type_; }
void ComplexInstrumentLeg::set_leg_security_type(LegSecurityType value) { leg_security_type_ = value; }

std::size_t ComplexInstrumentLeg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ComplexInstrumentLeg", wire_size, length);

    leg_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    leg_ratio_ = wire::read_i32_le(data + offset);
    offset += 4;

    leg_security_type_ = static_cast<LegSecurityType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t ComplexInstrumentLeg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexInstrumentLeg", wire_size, capacity);

    wire::write_text(data + offset, 8, ' ', leg_symbol_);
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(leg_ratio_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(leg_security_type_));
    offset += 1;

    return offset;
}

std::size_t ComplexInstrumentLeg::encoded_size() const {
    return wire_size;
}

void ComplexInstrumentLeg::print(std::ostream& out) const {
    out << "ComplexInstrumentLeg{";
    out << "leg_symbol=";
    print::text(out, leg_symbol_);
    out << ", leg_ratio=";
    out << leg_ratio_;
    out << ", leg_security_type=";
    out << leg_security_type_;
    out << '}';
}

bool ComplexInstrumentLeg::operator==(const ComplexInstrumentLeg& other) const {
    return leg_symbol_ == other.leg_symbol_
        && leg_ratio_ == other.leg_ratio_
        && leg_security_type_ == other.leg_security_type_;
}

bool ComplexInstrumentLeg::operator!=(const ComplexInstrumentLeg& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ComplexInstrumentLeg& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
