#include "LotTypeRulesGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

LotTypeRulesGroup::LotTypeRulesGroup(std::int8_t lot_type, std::optional<Decimal> min_lot_size)
  : lot_type_(lot_type), min_lot_size_(min_lot_size) {}

std::int8_t LotTypeRulesGroup::lot_type() const { return lot_type_; }
void LotTypeRulesGroup::set_lot_type(std::int8_t value) { lot_type_ = value; }

std::optional<Decimal> LotTypeRulesGroup::min_lot_size() const { return min_lot_size_; }
void LotTypeRulesGroup::set_min_lot_size(std::optional<Decimal> value) { min_lot_size_ = value; }

std::size_t LotTypeRulesGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LotTypeRulesGroup", wire_size, length);

    lot_type_ = wire::read_i8(data + offset);
    offset += 1;

    min_lot_size_ = wire::nullable_decimal(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL), -4);
    offset += 4;

    return offset;
}

std::size_t LotTypeRulesGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LotTypeRulesGroup", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(lot_type_));
    offset += 1;

    wire::write_i32_le(data + offset, min_lot_size_ ? static_cast<std::int32_t>(min_lot_size_->mantissa()) : static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    return offset;
}

std::size_t LotTypeRulesGroup::encoded_size() const {
    return wire_size;
}

void LotTypeRulesGroup::print(std::ostream& out) const {
    out << "LotTypeRulesGroup{";
    out << "lot_type=";
    out << static_cast<int>(lot_type_);
    out << ", min_lot_size=";
    print::optional(out, min_lot_size_);
    out << '}';
}

bool LotTypeRulesGroup::operator==(const LotTypeRulesGroup& other) const {
    return lot_type_ == other.lot_type_
        && min_lot_size_ == other.min_lot_size_;
}

bool LotTypeRulesGroup::operator!=(const LotTypeRulesGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const LotTypeRulesGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
