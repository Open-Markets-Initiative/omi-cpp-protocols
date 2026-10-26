#include "CombinationLeg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

CombinationLeg::CombinationLeg(std::uint32_t tradeable_instrument_id_leg, SideLeg side_leg, std::uint32_t ratio_leg, Decimal price_leg)
  : tradeable_instrument_id_leg_(tradeable_instrument_id_leg), side_leg_(side_leg), ratio_leg_(ratio_leg), price_leg_(price_leg) {}

std::uint32_t CombinationLeg::tradeable_instrument_id_leg() const { return tradeable_instrument_id_leg_; }
void CombinationLeg::set_tradeable_instrument_id_leg(std::uint32_t value) { tradeable_instrument_id_leg_ = value; }

SideLeg CombinationLeg::side_leg() const { return side_leg_; }
void CombinationLeg::set_side_leg(SideLeg value) { side_leg_ = value; }

std::uint32_t CombinationLeg::ratio_leg() const { return ratio_leg_; }
void CombinationLeg::set_ratio_leg(std::uint32_t value) { ratio_leg_ = value; }

Decimal CombinationLeg::price_leg() const { return price_leg_; }
void CombinationLeg::set_price_leg(Decimal value) { price_leg_ = value; }

std::size_t CombinationLeg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CombinationLeg", wire_size, length);

    tradeable_instrument_id_leg_ = wire::read_u32_be(data + offset);
    offset += 4;

    side_leg_ = static_cast<SideLeg>(wire::read_char(data + offset));
    offset += 1;

    ratio_leg_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_leg_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    return offset;
}

std::size_t CombinationLeg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CombinationLeg", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_leg_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_leg_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ratio_leg_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(price_leg_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t CombinationLeg::encoded_size() const {
    return wire_size;
}

void CombinationLeg::print(std::ostream& out) const {
    out << "CombinationLeg{";
    out << "tradeable_instrument_id_leg=";
    out << tradeable_instrument_id_leg_;
    out << ", side_leg=";
    out << side_leg_;
    out << ", ratio_leg=";
    out << ratio_leg_;
    out << ", price_leg=";
    out << price_leg_;
    out << '}';
}

bool CombinationLeg::operator==(const CombinationLeg& other) const {
    return tradeable_instrument_id_leg_ == other.tradeable_instrument_id_leg_
        && side_leg_ == other.side_leg_
        && ratio_leg_ == other.ratio_leg_
        && price_leg_ == other.price_leg_;
}

bool CombinationLeg::operator!=(const CombinationLeg& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CombinationLeg& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
