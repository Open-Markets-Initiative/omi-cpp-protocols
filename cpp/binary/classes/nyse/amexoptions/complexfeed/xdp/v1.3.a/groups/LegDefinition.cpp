#include "LegDefinition.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

LegDefinition::LegDefinition(std::uint32_t symbol_index, std::uint16_t leg_ratio_qty, Side side, LegSecurityType leg_security_type)
  : symbol_index_(symbol_index), leg_ratio_qty_(leg_ratio_qty), side_(side), leg_security_type_(leg_security_type) {}

std::uint32_t LegDefinition::symbol_index() const { return symbol_index_; }
void LegDefinition::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint16_t LegDefinition::leg_ratio_qty() const { return leg_ratio_qty_; }
void LegDefinition::set_leg_ratio_qty(std::uint16_t value) { leg_ratio_qty_ = value; }

Side LegDefinition::side() const { return side_; }
void LegDefinition::set_side(Side value) { side_ = value; }

LegSecurityType LegDefinition::leg_security_type() const { return leg_security_type_; }
void LegDefinition::set_leg_security_type(LegSecurityType value) { leg_security_type_ = value; }

std::size_t LegDefinition::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LegDefinition", wire_size, length);

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    leg_ratio_qty_ = wire::read_u16_le(data + offset);
    offset += 2;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    leg_security_type_ = static_cast<LegSecurityType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t LegDefinition::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LegDefinition", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(leg_ratio_qty_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(leg_security_type_));
    offset += 1;

    return offset;
}

std::size_t LegDefinition::encoded_size() const {
    return wire_size;
}

void LegDefinition::print(std::ostream& out) const {
    out << "LegDefinition{";
    out << "symbol_index=";
    out << symbol_index_;
    out << ", leg_ratio_qty=";
    out << leg_ratio_qty_;
    out << ", side=";
    out << side_;
    out << ", leg_security_type=";
    out << leg_security_type_;
    out << '}';
}

bool LegDefinition::operator==(const LegDefinition& other) const {
    return symbol_index_ == other.symbol_index_
        && leg_ratio_qty_ == other.leg_ratio_qty_
        && side_ == other.side_
        && leg_security_type_ == other.leg_security_type_;
}

bool LegDefinition::operator!=(const LegDefinition& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const LegDefinition& value) {
    value.print(out);
    return out;
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
