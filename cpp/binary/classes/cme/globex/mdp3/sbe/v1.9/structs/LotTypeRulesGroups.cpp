#include "LotTypeRulesGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

LotTypeRulesGroups::LotTypeRulesGroups(const GroupSize& group_size, const std::vector<LotTypeRulesGroup>& lot_type_rules_group)
  : group_size_(group_size), lot_type_rules_group_(lot_type_rules_group) {}

const GroupSize& LotTypeRulesGroups::group_size() const { return group_size_; }
GroupSize& LotTypeRulesGroups::group_size() { return group_size_; }
void LotTypeRulesGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<LotTypeRulesGroup>& LotTypeRulesGroups::lot_type_rules_group() const { return lot_type_rules_group_; }
std::vector<LotTypeRulesGroup>& LotTypeRulesGroups::lot_type_rules_group() { return lot_type_rules_group_; }
void LotTypeRulesGroups::set_lot_type_rules_group(const std::vector<LotTypeRulesGroup>& value) { lot_type_rules_group_ = value; }

std::size_t LotTypeRulesGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        lot_type_rules_group_.clear();
        lot_type_rules_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            LotTypeRulesGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("LotTypeRulesGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            lot_type_rules_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t LotTypeRulesGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LotTypeRulesGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(lot_type_rules_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(LotTypeRulesGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : lot_type_rules_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t LotTypeRulesGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(lot_type_rules_group_);
}

void LotTypeRulesGroups::print(std::ostream& out) const {
    out << "LotTypeRulesGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", lot_type_rules_group=";
    print::sequence(out, lot_type_rules_group_);
    out << '}';
}

bool LotTypeRulesGroups::operator==(const LotTypeRulesGroups& other) const {
    return group_size_ == other.group_size_
        && lot_type_rules_group_ == other.lot_type_rules_group_;
}

bool LotTypeRulesGroups::operator!=(const LotTypeRulesGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const LotTypeRulesGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
