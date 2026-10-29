#include "LegDefinition.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

LegDefinition::LegDefinition(std::uint32_t product_id, std::uint16_t leg_ratio_qty, LegSide leg_side, const std::array<std::byte, 8>& reserved_8)
  : product_id_(product_id), leg_ratio_qty_(leg_ratio_qty), leg_side_(leg_side), reserved_8_(reserved_8) {}

std::uint32_t LegDefinition::product_id() const { return product_id_; }
void LegDefinition::set_product_id(std::uint32_t value) { product_id_ = value; }

std::uint16_t LegDefinition::leg_ratio_qty() const { return leg_ratio_qty_; }
void LegDefinition::set_leg_ratio_qty(std::uint16_t value) { leg_ratio_qty_ = value; }

LegSide LegDefinition::leg_side() const { return leg_side_; }
void LegDefinition::set_leg_side(LegSide value) { leg_side_ = value; }

const std::array<std::byte, 8>& LegDefinition::reserved_8() const { return reserved_8_; }
std::array<std::byte, 8>& LegDefinition::reserved_8() { return reserved_8_; }
void LegDefinition::set_reserved_8(const std::array<std::byte, 8>& value) { reserved_8_ = value; }

std::size_t LegDefinition::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LegDefinition", wire_size, length);

    product_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    leg_ratio_qty_ = wire::read_u16_le(data + offset);
    offset += 2;

    leg_side_ = static_cast<LegSide>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    return offset;
}

std::size_t LegDefinition::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LegDefinition", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(product_id_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(leg_ratio_qty_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(leg_side_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    return offset;
}

std::size_t LegDefinition::encoded_size() const {
    return wire_size;
}

void LegDefinition::print(std::ostream& out) const {
    out << "LegDefinition{";
    out << "product_id=";
    out << product_id_;
    out << ", leg_ratio_qty=";
    out << leg_ratio_qty_;
    out << ", leg_side=";
    out << leg_side_;
    out << ", reserved_8=";
    print::hex(out, reserved_8_.data(), reserved_8_.size());
    out << '}';
}

bool LegDefinition::operator==(const LegDefinition& other) const {
    return product_id_ == other.product_id_
        && leg_ratio_qty_ == other.leg_ratio_qty_
        && leg_side_ == other.leg_side_
        && reserved_8_ == other.reserved_8_;
}

bool LegDefinition::operator!=(const LegDefinition& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const LegDefinition& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
