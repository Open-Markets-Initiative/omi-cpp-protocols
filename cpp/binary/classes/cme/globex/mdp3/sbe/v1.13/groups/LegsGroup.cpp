#include "LegsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

LegsGroup::LegsGroup(std::int32_t leg_security_id, LegSide leg_side, std::int8_t leg_ratio_qty, std::optional<Decimal> leg_price, std::optional<Decimal> leg_option_delta)
  : leg_security_id_(leg_security_id), leg_side_(leg_side), leg_ratio_qty_(leg_ratio_qty), leg_price_(leg_price), leg_option_delta_(leg_option_delta) {}

std::int32_t LegsGroup::leg_security_id() const { return leg_security_id_; }
void LegsGroup::set_leg_security_id(std::int32_t value) { leg_security_id_ = value; }

LegSide LegsGroup::leg_side() const { return leg_side_; }
void LegsGroup::set_leg_side(LegSide value) { leg_side_ = value; }

std::int8_t LegsGroup::leg_ratio_qty() const { return leg_ratio_qty_; }
void LegsGroup::set_leg_ratio_qty(std::int8_t value) { leg_ratio_qty_ = value; }

std::optional<Decimal> LegsGroup::leg_price() const { return leg_price_; }
void LegsGroup::set_leg_price(std::optional<Decimal> value) { leg_price_ = value; }

std::optional<Decimal> LegsGroup::leg_option_delta() const { return leg_option_delta_; }
void LegsGroup::set_leg_option_delta(std::optional<Decimal> value) { leg_option_delta_ = value; }

std::size_t LegsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LegsGroup", wire_size, length);

    leg_security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    leg_side_ = static_cast<LegSide>(wire::read_u8(data + offset));
    offset += 1;

    leg_ratio_qty_ = wire::read_i8(data + offset);
    offset += 1;

    leg_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    leg_option_delta_ = wire::nullable_decimal(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL), -4);
    offset += 4;

    return offset;
}

std::size_t LegsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LegsGroup", wire_size, capacity);

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(leg_security_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(leg_side_));
    offset += 1;

    wire::write_i8(data + offset, static_cast<std::int8_t>(leg_ratio_qty_));
    offset += 1;

    wire::write_i64_le(data + offset, leg_price_ ? static_cast<std::int64_t>(leg_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i32_le(data + offset, leg_option_delta_ ? static_cast<std::int32_t>(leg_option_delta_->mantissa()) : static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    return offset;
}

std::size_t LegsGroup::encoded_size() const {
    return wire_size;
}

void LegsGroup::print(std::ostream& out) const {
    out << "LegsGroup{";
    out << "leg_security_id=";
    out << leg_security_id_;
    out << ", leg_side=";
    out << leg_side_;
    out << ", leg_ratio_qty=";
    out << static_cast<int>(leg_ratio_qty_);
    out << ", leg_price=";
    print::optional(out, leg_price_);
    out << ", leg_option_delta=";
    print::optional(out, leg_option_delta_);
    out << '}';
}

bool LegsGroup::operator==(const LegsGroup& other) const {
    return leg_security_id_ == other.leg_security_id_
        && leg_side_ == other.leg_side_
        && leg_ratio_qty_ == other.leg_ratio_qty_
        && leg_price_ == other.leg_price_
        && leg_option_delta_ == other.leg_option_delta_;
}

bool LegsGroup::operator!=(const LegsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const LegsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
