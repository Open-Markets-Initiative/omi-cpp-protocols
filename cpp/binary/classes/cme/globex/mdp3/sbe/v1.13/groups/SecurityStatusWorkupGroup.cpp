#include "SecurityStatusWorkupGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

SecurityStatusWorkupGroup::SecurityStatusWorkupGroup(std::uint64_t order_id, Side side, std::optional<AggressorIndicator> aggressor_indicator)
  : order_id_(order_id), side_(side), aggressor_indicator_(aggressor_indicator) {}

std::uint64_t SecurityStatusWorkupGroup::order_id() const { return order_id_; }
void SecurityStatusWorkupGroup::set_order_id(std::uint64_t value) { order_id_ = value; }

Side SecurityStatusWorkupGroup::side() const { return side_; }
void SecurityStatusWorkupGroup::set_side(Side value) { side_ = value; }

std::optional<AggressorIndicator> SecurityStatusWorkupGroup::aggressor_indicator() const { return aggressor_indicator_; }
void SecurityStatusWorkupGroup::set_aggressor_indicator(std::optional<AggressorIndicator> value) { aggressor_indicator_ = value; }

std::size_t SecurityStatusWorkupGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityStatusWorkupGroup", wire_size, length);

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    side_ = static_cast<Side>(wire::read_u8(data + offset));
    offset += 1;

    aggressor_indicator_ = wire::nullable_enum<AggressorIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    return offset;
}

std::size_t SecurityStatusWorkupGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityStatusWorkupGroup", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(side_));
    offset += 1;

    wire::write_u8(data + offset, aggressor_indicator_ ? static_cast<std::uint8_t>(*aggressor_indicator_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    return offset;
}

std::size_t SecurityStatusWorkupGroup::encoded_size() const {
    return wire_size;
}

void SecurityStatusWorkupGroup::print(std::ostream& out) const {
    out << "SecurityStatusWorkupGroup{";
    out << "order_id=";
    out << order_id_;
    out << ", side=";
    out << side_;
    out << ", aggressor_indicator=";
    print::optional(out, aggressor_indicator_);
    out << '}';
}

bool SecurityStatusWorkupGroup::operator==(const SecurityStatusWorkupGroup& other) const {
    return order_id_ == other.order_id_
        && side_ == other.side_
        && aggressor_indicator_ == other.aggressor_indicator_;
}

bool SecurityStatusWorkupGroup::operator!=(const SecurityStatusWorkupGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityStatusWorkupGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
