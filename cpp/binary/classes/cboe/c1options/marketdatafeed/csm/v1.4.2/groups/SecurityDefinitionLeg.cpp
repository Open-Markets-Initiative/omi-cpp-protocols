#include "SecurityDefinitionLeg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

SecurityDefinitionLeg::SecurityDefinitionLeg(std::uint32_t leg_ratio_qty, std::uint32_t leg_security_id, LegSide leg_side)
  : leg_ratio_qty_(leg_ratio_qty), leg_security_id_(leg_security_id), leg_side_(leg_side) {}

std::uint32_t SecurityDefinitionLeg::leg_ratio_qty() const { return leg_ratio_qty_; }
void SecurityDefinitionLeg::set_leg_ratio_qty(std::uint32_t value) { leg_ratio_qty_ = value; }

std::uint32_t SecurityDefinitionLeg::leg_security_id() const { return leg_security_id_; }
void SecurityDefinitionLeg::set_leg_security_id(std::uint32_t value) { leg_security_id_ = value; }

LegSide SecurityDefinitionLeg::leg_side() const { return leg_side_; }
void SecurityDefinitionLeg::set_leg_side(LegSide value) { leg_side_ = value; }

std::size_t SecurityDefinitionLeg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityDefinitionLeg", wire_size, length);

    leg_ratio_qty_ = wire::read_u32_be(data + offset);
    offset += 4;

    leg_security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    leg_side_ = static_cast<LegSide>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SecurityDefinitionLeg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityDefinitionLeg", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(leg_ratio_qty_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(leg_security_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(leg_side_));
    offset += 1;

    return offset;
}

std::size_t SecurityDefinitionLeg::encoded_size() const {
    return wire_size;
}

void SecurityDefinitionLeg::print(std::ostream& out) const {
    out << "SecurityDefinitionLeg{";
    out << "leg_ratio_qty=";
    out << leg_ratio_qty_;
    out << ", leg_security_id=";
    out << leg_security_id_;
    out << ", leg_side=";
    out << leg_side_;
    out << '}';
}

bool SecurityDefinitionLeg::operator==(const SecurityDefinitionLeg& other) const {
    return leg_ratio_qty_ == other.leg_ratio_qty_
        && leg_security_id_ == other.leg_security_id_
        && leg_side_ == other.leg_side_;
}

bool SecurityDefinitionLeg::operator!=(const SecurityDefinitionLeg& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityDefinitionLeg& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
