#include "InstrumentLeg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

InstrumentLeg::InstrumentLeg(std::uint32_t instrument_id, std::int32_t leg_ratio_and_side, std::uint32_t maturity_month_year, const std::array<std::byte, 8>& reserved_8)
  : instrument_id_(instrument_id), leg_ratio_and_side_(leg_ratio_and_side), maturity_month_year_(maturity_month_year), reserved_8_(reserved_8) {}

std::uint32_t InstrumentLeg::instrument_id() const { return instrument_id_; }
void InstrumentLeg::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

std::int32_t InstrumentLeg::leg_ratio_and_side() const { return leg_ratio_and_side_; }
void InstrumentLeg::set_leg_ratio_and_side(std::int32_t value) { leg_ratio_and_side_ = value; }

std::uint32_t InstrumentLeg::maturity_month_year() const { return maturity_month_year_; }
void InstrumentLeg::set_maturity_month_year(std::uint32_t value) { maturity_month_year_ = value; }

const std::array<std::byte, 8>& InstrumentLeg::reserved_8() const { return reserved_8_; }
std::array<std::byte, 8>& InstrumentLeg::reserved_8() { return reserved_8_; }
void InstrumentLeg::set_reserved_8(const std::array<std::byte, 8>& value) { reserved_8_ = value; }

std::size_t InstrumentLeg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrumentLeg", wire_size, length);

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    leg_ratio_and_side_ = wire::read_i32_le(data + offset);
    offset += 4;

    maturity_month_year_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    return offset;
}

std::size_t InstrumentLeg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrumentLeg", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(leg_ratio_and_side_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(maturity_month_year_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    return offset;
}

std::size_t InstrumentLeg::encoded_size() const {
    return wire_size;
}

void InstrumentLeg::print(std::ostream& out) const {
    out << "InstrumentLeg{";
    out << "instrument_id=";
    out << instrument_id_;
    out << ", leg_ratio_and_side=";
    out << leg_ratio_and_side_;
    out << ", maturity_month_year=";
    out << maturity_month_year_;
    out << ", reserved_8=";
    print::hex(out, reserved_8_.data(), reserved_8_.size());
    out << '}';
}

bool InstrumentLeg::operator==(const InstrumentLeg& other) const {
    return instrument_id_ == other.instrument_id_
        && leg_ratio_and_side_ == other.leg_ratio_and_side_
        && maturity_month_year_ == other.maturity_month_year_
        && reserved_8_ == other.reserved_8_;
}

bool InstrumentLeg::operator!=(const InstrumentLeg& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const InstrumentLeg& value) {
    value.print(out);
    return out;
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
