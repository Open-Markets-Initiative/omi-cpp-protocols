#include "LegsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

LegsGroup::LegsGroup(std::uint64_t leg_security_id, std::optional<Decimal> leg_ratio_qty, LegSecurityType leg_security_type, LegSide leg_side, const std::string& leg_symbol)
  : leg_security_id_(leg_security_id), leg_ratio_qty_(leg_ratio_qty), leg_security_type_(leg_security_type), leg_side_(leg_side), leg_symbol_(leg_symbol) {}

std::uint64_t LegsGroup::leg_security_id() const { return leg_security_id_; }
void LegsGroup::set_leg_security_id(std::uint64_t value) { leg_security_id_ = value; }

std::optional<Decimal> LegsGroup::leg_ratio_qty() const { return leg_ratio_qty_; }
void LegsGroup::set_leg_ratio_qty(std::optional<Decimal> value) { leg_ratio_qty_ = value; }

LegSecurityType LegsGroup::leg_security_type() const { return leg_security_type_; }
void LegsGroup::set_leg_security_type(LegSecurityType value) { leg_security_type_ = value; }

LegSide LegsGroup::leg_side() const { return leg_side_; }
void LegsGroup::set_leg_side(LegSide value) { leg_side_ = value; }

const std::string& LegsGroup::leg_symbol() const { return leg_symbol_; }
std::string& LegsGroup::leg_symbol() { return leg_symbol_; }
void LegsGroup::set_leg_symbol(const std::string& value) { leg_symbol_ = value; }

std::size_t LegsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LegsGroup", wire_size, length);

    leg_security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    leg_ratio_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -7);
    offset += 8;

    leg_security_type_ = static_cast<LegSecurityType>(wire::read_u8(data + offset));
    offset += 1;

    leg_side_ = static_cast<LegSide>(wire::read_u8(data + offset));
    offset += 1;

    leg_symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    return offset;
}

std::size_t LegsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LegsGroup", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(leg_security_id_));
    offset += 8;

    wire::write_i64_le(data + offset, leg_ratio_qty_ ? static_cast<std::int64_t>(leg_ratio_qty_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(leg_security_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(leg_side_));
    offset += 1;

    wire::write_text(data + offset, 20, '\0', leg_symbol_);
    offset += 20;

    return offset;
}

std::size_t LegsGroup::encoded_size() const {
    return wire_size;
}

void LegsGroup::print(std::ostream& out) const {
    out << "LegsGroup{";
    out << "leg_security_id=";
    out << leg_security_id_;
    out << ", leg_ratio_qty=";
    print::optional(out, leg_ratio_qty_);
    out << ", leg_security_type=";
    out << leg_security_type_;
    out << ", leg_side=";
    out << leg_side_;
    out << ", leg_symbol=";
    print::text(out, leg_symbol_);
    out << '}';
}

bool LegsGroup::operator==(const LegsGroup& other) const {
    return leg_security_id_ == other.leg_security_id_
        && leg_ratio_qty_ == other.leg_ratio_qty_
        && leg_security_type_ == other.leg_security_type_
        && leg_side_ == other.leg_side_
        && leg_symbol_ == other.leg_symbol_;
}

bool LegsGroup::operator!=(const LegsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const LegsGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
