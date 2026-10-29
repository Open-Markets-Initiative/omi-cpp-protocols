#include "LegsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

LegsGroup::LegsGroup(const std::string& leg_symbol, Decimal leg_ratio_qty, LegSide leg_side, const std::array<std::byte, 1>& padding_1)
  : leg_symbol_(leg_symbol), leg_ratio_qty_(leg_ratio_qty), leg_side_(leg_side), padding_1_(padding_1) {}

const std::string& LegsGroup::leg_symbol() const { return leg_symbol_; }
std::string& LegsGroup::leg_symbol() { return leg_symbol_; }
void LegsGroup::set_leg_symbol(const std::string& value) { leg_symbol_ = value; }

Decimal LegsGroup::leg_ratio_qty() const { return leg_ratio_qty_; }
void LegsGroup::set_leg_ratio_qty(Decimal value) { leg_ratio_qty_ = value; }

LegSide LegsGroup::leg_side() const { return leg_side_; }
void LegsGroup::set_leg_side(LegSide value) { leg_side_ = value; }

const std::array<std::byte, 1>& LegsGroup::padding_1() const { return padding_1_; }
std::array<std::byte, 1>& LegsGroup::padding_1() { return padding_1_; }
void LegsGroup::set_padding_1(const std::array<std::byte, 1>& value) { padding_1_ = value; }

std::size_t LegsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LegsGroup", wire_size, length);

    leg_symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    leg_ratio_qty_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -7);
    offset += 8;

    leg_side_ = static_cast<LegSide>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, padding_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t LegsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LegsGroup", wire_size, capacity);

    wire::write_text(data + offset, 20, '\0', leg_symbol_);
    offset += 20;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(leg_ratio_qty_.mantissa()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(leg_side_));
    offset += 1;

    wire::write_bytes(data + offset, padding_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t LegsGroup::encoded_size() const {
    return wire_size;
}

void LegsGroup::print(std::ostream& out) const {
    out << "LegsGroup{";
    out << "leg_symbol=";
    print::text(out, leg_symbol_);
    out << ", leg_ratio_qty=";
    out << leg_ratio_qty_;
    out << ", leg_side=";
    out << leg_side_;
    out << ", padding_1=";
    print::hex(out, padding_1_.data(), padding_1_.size());
    out << '}';
}

bool LegsGroup::operator==(const LegsGroup& other) const {
    return leg_symbol_ == other.leg_symbol_
        && leg_ratio_qty_ == other.leg_ratio_qty_
        && leg_side_ == other.leg_side_
        && padding_1_ == other.padding_1_;
}

bool LegsGroup::operator!=(const LegsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const LegsGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
