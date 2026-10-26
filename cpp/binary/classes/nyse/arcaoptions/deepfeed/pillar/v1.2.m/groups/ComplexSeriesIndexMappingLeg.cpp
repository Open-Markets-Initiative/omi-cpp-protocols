#include "ComplexSeriesIndexMappingLeg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

ComplexSeriesIndexMappingLeg::ComplexSeriesIndexMappingLeg(std::uint32_t symbol_index, std::uint16_t leg_ratio_qty, LegSide leg_side, LegSecurityType leg_security_type)
  : symbol_index_(symbol_index), leg_ratio_qty_(leg_ratio_qty), leg_side_(leg_side), leg_security_type_(leg_security_type) {}

std::uint32_t ComplexSeriesIndexMappingLeg::symbol_index() const { return symbol_index_; }
void ComplexSeriesIndexMappingLeg::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint16_t ComplexSeriesIndexMappingLeg::leg_ratio_qty() const { return leg_ratio_qty_; }
void ComplexSeriesIndexMappingLeg::set_leg_ratio_qty(std::uint16_t value) { leg_ratio_qty_ = value; }

LegSide ComplexSeriesIndexMappingLeg::leg_side() const { return leg_side_; }
void ComplexSeriesIndexMappingLeg::set_leg_side(LegSide value) { leg_side_ = value; }

LegSecurityType ComplexSeriesIndexMappingLeg::leg_security_type() const { return leg_security_type_; }
void ComplexSeriesIndexMappingLeg::set_leg_security_type(LegSecurityType value) { leg_security_type_ = value; }

std::size_t ComplexSeriesIndexMappingLeg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ComplexSeriesIndexMappingLeg", wire_size, length);

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    leg_ratio_qty_ = wire::read_u16_le(data + offset);
    offset += 2;

    leg_side_ = static_cast<LegSide>(wire::read_char(data + offset));
    offset += 1;

    leg_security_type_ = static_cast<LegSecurityType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t ComplexSeriesIndexMappingLeg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexSeriesIndexMappingLeg", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(leg_ratio_qty_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(leg_side_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(leg_security_type_));
    offset += 1;

    return offset;
}

std::size_t ComplexSeriesIndexMappingLeg::encoded_size() const {
    return wire_size;
}

void ComplexSeriesIndexMappingLeg::print(std::ostream& out) const {
    out << "ComplexSeriesIndexMappingLeg{";
    out << "symbol_index=";
    out << symbol_index_;
    out << ", leg_ratio_qty=";
    out << leg_ratio_qty_;
    out << ", leg_side=";
    out << leg_side_;
    out << ", leg_security_type=";
    out << leg_security_type_;
    out << '}';
}

bool ComplexSeriesIndexMappingLeg::operator==(const ComplexSeriesIndexMappingLeg& other) const {
    return symbol_index_ == other.symbol_index_
        && leg_ratio_qty_ == other.leg_ratio_qty_
        && leg_side_ == other.leg_side_
        && leg_security_type_ == other.leg_security_type_;
}

bool ComplexSeriesIndexMappingLeg::operator!=(const ComplexSeriesIndexMappingLeg& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ComplexSeriesIndexMappingLeg& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
