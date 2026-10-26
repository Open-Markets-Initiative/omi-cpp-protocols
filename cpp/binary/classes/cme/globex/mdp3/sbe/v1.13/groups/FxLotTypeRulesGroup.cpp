#include "FxLotTypeRulesGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

FxLotTypeRulesGroup::FxLotTypeRulesGroup(std::int8_t lot_type, std::uint64_t min_lot_size_u_int_64)
  : lot_type_(lot_type), min_lot_size_u_int_64_(min_lot_size_u_int_64) {}

std::int8_t FxLotTypeRulesGroup::lot_type() const { return lot_type_; }
void FxLotTypeRulesGroup::set_lot_type(std::int8_t value) { lot_type_ = value; }

std::uint64_t FxLotTypeRulesGroup::min_lot_size_u_int_64() const { return min_lot_size_u_int_64_; }
void FxLotTypeRulesGroup::set_min_lot_size_u_int_64(std::uint64_t value) { min_lot_size_u_int_64_ = value; }

std::size_t FxLotTypeRulesGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FxLotTypeRulesGroup", wire_size, length);

    lot_type_ = wire::read_i8(data + offset);
    offset += 1;

    min_lot_size_u_int_64_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t FxLotTypeRulesGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FxLotTypeRulesGroup", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(lot_type_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(min_lot_size_u_int_64_));
    offset += 8;

    return offset;
}

std::size_t FxLotTypeRulesGroup::encoded_size() const {
    return wire_size;
}

void FxLotTypeRulesGroup::print(std::ostream& out) const {
    out << "FxLotTypeRulesGroup{";
    out << "lot_type=";
    out << static_cast<int>(lot_type_);
    out << ", min_lot_size_u_int_64=";
    out << min_lot_size_u_int_64_;
    out << '}';
}

bool FxLotTypeRulesGroup::operator==(const FxLotTypeRulesGroup& other) const {
    return lot_type_ == other.lot_type_
        && min_lot_size_u_int_64_ == other.min_lot_size_u_int_64_;
}

bool FxLotTypeRulesGroup::operator!=(const FxLotTypeRulesGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const FxLotTypeRulesGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
