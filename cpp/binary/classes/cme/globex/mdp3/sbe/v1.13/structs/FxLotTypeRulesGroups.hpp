#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/FxLotTypeRulesGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NoLotTypeRules Block
class FxLotTypeRulesGroups {
  public:

    FxLotTypeRulesGroups() = default;
    FxLotTypeRulesGroups(const GroupSize& group_size, const std::vector<FxLotTypeRulesGroup>& fx_lot_type_rules_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Fx Lot Type Rules Group: Number of LotTypeRules entries
    const std::vector<FxLotTypeRulesGroup>& fx_lot_type_rules_group() const;
    std::vector<FxLotTypeRulesGroup>& fx_lot_type_rules_group();
    void set_fx_lot_type_rules_group(const std::vector<FxLotTypeRulesGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const FxLotTypeRulesGroups& other) const;
    bool operator!=(const FxLotTypeRulesGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<FxLotTypeRulesGroup> fx_lot_type_rules_group_{};
};

std::ostream& operator<<(std::ostream& out, const FxLotTypeRulesGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_13
