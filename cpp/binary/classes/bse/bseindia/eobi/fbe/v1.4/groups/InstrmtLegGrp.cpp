#include "InstrmtLegGrp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

InstrmtLegGrp::InstrmtLegGrp(std::int64_t leg_security_id, std::optional<std::int32_t> leg_ratio_qty, LegSide leg_side, const std::array<std::byte, 3>& pad_3)
  : leg_security_id_(leg_security_id), leg_ratio_qty_(leg_ratio_qty), leg_side_(leg_side), pad_3_(pad_3) {}

std::int64_t InstrmtLegGrp::leg_security_id() const { return leg_security_id_; }
void InstrmtLegGrp::set_leg_security_id(std::int64_t value) { leg_security_id_ = value; }

std::optional<std::int32_t> InstrmtLegGrp::leg_ratio_qty() const { return leg_ratio_qty_; }
void InstrmtLegGrp::set_leg_ratio_qty(std::optional<std::int32_t> value) { leg_ratio_qty_ = value; }

LegSide InstrmtLegGrp::leg_side() const { return leg_side_; }
void InstrmtLegGrp::set_leg_side(LegSide value) { leg_side_ = value; }

const std::array<std::byte, 3>& InstrmtLegGrp::pad_3() const { return pad_3_; }
std::array<std::byte, 3>& InstrmtLegGrp::pad_3() { return pad_3_; }
void InstrmtLegGrp::set_pad_3(const std::array<std::byte, 3>& value) { pad_3_ = value; }

std::size_t InstrmtLegGrp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrmtLegGrp", wire_size, length);

    leg_security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    leg_ratio_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(-2147483648LL));
    offset += 4;

    leg_side_ = static_cast<LegSide>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, pad_3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t InstrmtLegGrp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrmtLegGrp", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(leg_security_id_));
    offset += 8;

    wire::write_i32_le(data + offset, leg_ratio_qty_.value_or(static_cast<std::int32_t>(-2147483648LL)));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(leg_side_));
    offset += 1;

    wire::write_bytes(data + offset, pad_3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t InstrmtLegGrp::encoded_size() const {
    return wire_size;
}

void InstrmtLegGrp::print(std::ostream& out) const {
    out << "InstrmtLegGrp{";
    out << "leg_security_id=";
    out << leg_security_id_;
    out << ", leg_ratio_qty=";
    print::optional(out, leg_ratio_qty_);
    out << ", leg_side=";
    out << leg_side_;
    out << ", pad_3=";
    print::hex(out, pad_3_.data(), pad_3_.size());
    out << '}';
}

bool InstrmtLegGrp::operator==(const InstrmtLegGrp& other) const {
    return leg_security_id_ == other.leg_security_id_
        && leg_ratio_qty_ == other.leg_ratio_qty_
        && leg_side_ == other.leg_side_
        && pad_3_ == other.pad_3_;
}

bool InstrmtLegGrp::operator!=(const InstrmtLegGrp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const InstrmtLegGrp& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
