#include "CombinationOrderbookLeg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

CombinationOrderbookLeg::CombinationOrderbookLeg(std::chrono::nanoseconds nanoseconds, std::uint32_t combination_orderbook_id, std::uint32_t leg_orderbook_id, LegSide leg_side, std::uint32_t leg_ratio)
  : nanoseconds_(nanoseconds), combination_orderbook_id_(combination_orderbook_id), leg_orderbook_id_(leg_orderbook_id), leg_side_(leg_side), leg_ratio_(leg_ratio) {}

std::chrono::nanoseconds CombinationOrderbookLeg::nanoseconds() const { return nanoseconds_; }
void CombinationOrderbookLeg::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t CombinationOrderbookLeg::combination_orderbook_id() const { return combination_orderbook_id_; }
void CombinationOrderbookLeg::set_combination_orderbook_id(std::uint32_t value) { combination_orderbook_id_ = value; }

std::uint32_t CombinationOrderbookLeg::leg_orderbook_id() const { return leg_orderbook_id_; }
void CombinationOrderbookLeg::set_leg_orderbook_id(std::uint32_t value) { leg_orderbook_id_ = value; }

LegSide CombinationOrderbookLeg::leg_side() const { return leg_side_; }
void CombinationOrderbookLeg::set_leg_side(LegSide value) { leg_side_ = value; }

std::uint32_t CombinationOrderbookLeg::leg_ratio() const { return leg_ratio_; }
void CombinationOrderbookLeg::set_leg_ratio(std::uint32_t value) { leg_ratio_ = value; }

MessageCode CombinationOrderbookLeg::type() const { return message_type; }

std::string_view CombinationOrderbookLeg::name() const { return "Combination Orderbook Leg"; }

std::size_t CombinationOrderbookLeg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CombinationOrderbookLeg", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    combination_orderbook_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    leg_orderbook_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    leg_side_ = static_cast<LegSide>(wire::read_char(data + offset));
    offset += 1;

    leg_ratio_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t CombinationOrderbookLeg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CombinationOrderbookLeg", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(combination_orderbook_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(leg_orderbook_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(leg_side_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(leg_ratio_));
    offset += 4;

    return offset;
}

std::size_t CombinationOrderbookLeg::encoded_size() const {
    return wire_size;
}

void CombinationOrderbookLeg::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> CombinationOrderbookLeg::clone() const {
    return std::make_unique<CombinationOrderbookLeg>(*this);
}

void CombinationOrderbookLeg::print(std::ostream& out) const {
    out << "CombinationOrderbookLeg{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", combination_orderbook_id=";
    out << combination_orderbook_id_;
    out << ", leg_orderbook_id=";
    out << leg_orderbook_id_;
    out << ", leg_side=";
    out << leg_side_;
    out << ", leg_ratio=";
    out << leg_ratio_;
    out << '}';
}

bool CombinationOrderbookLeg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const CombinationOrderbookLeg*>(&other);
    return that != nullptr && *this == *that;
}

bool CombinationOrderbookLeg::operator==(const CombinationOrderbookLeg& other) const {
    return nanoseconds_ == other.nanoseconds_
        && combination_orderbook_id_ == other.combination_orderbook_id_
        && leg_orderbook_id_ == other.leg_orderbook_id_
        && leg_side_ == other.leg_side_
        && leg_ratio_ == other.leg_ratio_;
}

bool CombinationOrderbookLeg::operator!=(const CombinationOrderbookLeg& other) const {
    return !(*this == other);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
