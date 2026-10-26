#include "InstrmtLegGrpComp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

InstrmtLegGrpComp::InstrmtLegGrpComp(std::optional<std::int32_t> leg_symbol, const std::array<std::byte, 4>& pad4, std::optional<std::int64_t> leg_security_id, std::optional<Decimal> leg_price, std::optional<std::int32_t> leg_ratio_qty, std::optional<LegSecurityType> leg_security_type, std::optional<LegSide> leg_side, const std::array<std::byte, 2>& pad2)
  : leg_symbol_(leg_symbol), pad4_(pad4), leg_security_id_(leg_security_id), leg_price_(leg_price), leg_ratio_qty_(leg_ratio_qty), leg_security_type_(leg_security_type), leg_side_(leg_side), pad2_(pad2) {}

std::optional<std::int32_t> InstrmtLegGrpComp::leg_symbol() const { return leg_symbol_; }
void InstrmtLegGrpComp::set_leg_symbol(std::optional<std::int32_t> value) { leg_symbol_ = value; }

const std::array<std::byte, 4>& InstrmtLegGrpComp::pad4() const { return pad4_; }
std::array<std::byte, 4>& InstrmtLegGrpComp::pad4() { return pad4_; }
void InstrmtLegGrpComp::set_pad4(const std::array<std::byte, 4>& value) { pad4_ = value; }

std::optional<std::int64_t> InstrmtLegGrpComp::leg_security_id() const { return leg_security_id_; }
void InstrmtLegGrpComp::set_leg_security_id(std::optional<std::int64_t> value) { leg_security_id_ = value; }

std::optional<Decimal> InstrmtLegGrpComp::leg_price() const { return leg_price_; }
void InstrmtLegGrpComp::set_leg_price(std::optional<Decimal> value) { leg_price_ = value; }

std::optional<std::int32_t> InstrmtLegGrpComp::leg_ratio_qty() const { return leg_ratio_qty_; }
void InstrmtLegGrpComp::set_leg_ratio_qty(std::optional<std::int32_t> value) { leg_ratio_qty_ = value; }

std::optional<LegSecurityType> InstrmtLegGrpComp::leg_security_type() const { return leg_security_type_; }
void InstrmtLegGrpComp::set_leg_security_type(std::optional<LegSecurityType> value) { leg_security_type_ = value; }

std::optional<LegSide> InstrmtLegGrpComp::leg_side() const { return leg_side_; }
void InstrmtLegGrpComp::set_leg_side(std::optional<LegSide> value) { leg_side_ = value; }

const std::array<std::byte, 2>& InstrmtLegGrpComp::pad2() const { return pad2_; }
std::array<std::byte, 2>& InstrmtLegGrpComp::pad2() { return pad2_; }
void InstrmtLegGrpComp::set_pad2(const std::array<std::byte, 2>& value) { pad2_ = value; }

std::size_t InstrmtLegGrpComp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrmtLegGrpComp", wire_size, length);

    leg_symbol_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    wire::read_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    leg_security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    leg_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    leg_ratio_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    leg_security_type_ = wire::nullable_enum<LegSecurityType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    leg_side_ = wire::nullable_enum<LegSide>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t InstrmtLegGrpComp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrmtLegGrpComp", wire_size, capacity);

    wire::write_i32_le(data + offset, leg_symbol_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    wire::write_i64_le(data + offset, leg_security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_i64_le(data + offset, leg_price_ ? static_cast<std::int64_t>(leg_price_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i32_le(data + offset, leg_ratio_qty_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_u8(data + offset, leg_security_type_ ? static_cast<std::uint8_t>(*leg_security_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, leg_side_ ? static_cast<std::uint8_t>(*leg_side_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t InstrmtLegGrpComp::encoded_size() const {
    return wire_size;
}

void InstrmtLegGrpComp::print(std::ostream& out) const {
    out << "InstrmtLegGrpComp{";
    out << "leg_symbol=";
    print::optional(out, leg_symbol_);
    out << ", pad4=";
    print::hex(out, pad4_.data(), pad4_.size());
    out << ", leg_security_id=";
    print::optional(out, leg_security_id_);
    out << ", leg_price=";
    print::optional(out, leg_price_);
    out << ", leg_ratio_qty=";
    print::optional(out, leg_ratio_qty_);
    out << ", leg_security_type=";
    print::optional(out, leg_security_type_);
    out << ", leg_side=";
    print::optional(out, leg_side_);
    out << ", pad2=";
    print::hex(out, pad2_.data(), pad2_.size());
    out << '}';
}

bool InstrmtLegGrpComp::operator==(const InstrmtLegGrpComp& other) const {
    return leg_symbol_ == other.leg_symbol_
        && pad4_ == other.pad4_
        && leg_security_id_ == other.leg_security_id_
        && leg_price_ == other.leg_price_
        && leg_ratio_qty_ == other.leg_ratio_qty_
        && leg_security_type_ == other.leg_security_type_
        && leg_side_ == other.leg_side_
        && pad2_ == other.pad2_;
}

bool InstrmtLegGrpComp::operator!=(const InstrmtLegGrpComp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const InstrmtLegGrpComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v13_0
