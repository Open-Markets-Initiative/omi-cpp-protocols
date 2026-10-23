#include "FxLotTypeRulesGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

FxLotTypeRulesGroups::FxLotTypeRulesGroups(const GroupSize& group_size, const std::vector<FxLotTypeRulesGroup>& fx_lot_type_rules_group)
  : group_size_(group_size), fx_lot_type_rules_group_(fx_lot_type_rules_group) {}

const GroupSize& FxLotTypeRulesGroups::group_size() const { return group_size_; }
GroupSize& FxLotTypeRulesGroups::group_size() { return group_size_; }
void FxLotTypeRulesGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<FxLotTypeRulesGroup>& FxLotTypeRulesGroups::fx_lot_type_rules_group() const { return fx_lot_type_rules_group_; }
std::vector<FxLotTypeRulesGroup>& FxLotTypeRulesGroups::fx_lot_type_rules_group() { return fx_lot_type_rules_group_; }
void FxLotTypeRulesGroups::set_fx_lot_type_rules_group(const std::vector<FxLotTypeRulesGroup>& value) { fx_lot_type_rules_group_ = value; }

std::size_t FxLotTypeRulesGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        fx_lot_type_rules_group_.clear();
        fx_lot_type_rules_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            FxLotTypeRulesGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("FxLotTypeRulesGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            fx_lot_type_rules_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t FxLotTypeRulesGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FxLotTypeRulesGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(fx_lot_type_rules_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(FxLotTypeRulesGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : fx_lot_type_rules_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t FxLotTypeRulesGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(fx_lot_type_rules_group_);
}

void FxLotTypeRulesGroups::print(std::ostream& out) const {
    out << "FxLotTypeRulesGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", fx_lot_type_rules_group=";
    print::sequence(out, fx_lot_type_rules_group_);
    out << '}';
}

bool FxLotTypeRulesGroups::operator==(const FxLotTypeRulesGroups& other) const {
    return group_size_ == other.group_size_
        && fx_lot_type_rules_group_ == other.fx_lot_type_rules_group_;
}

bool FxLotTypeRulesGroups::operator!=(const FxLotTypeRulesGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const FxLotTypeRulesGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
