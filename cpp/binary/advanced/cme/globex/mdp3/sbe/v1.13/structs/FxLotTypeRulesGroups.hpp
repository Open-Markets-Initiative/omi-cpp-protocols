#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

struct fx_lot_type_rules_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static fx_lot_type_rules_groups* parse(std::byte* buffer) {
        return reinterpret_cast<fx_lot_type_rules_groups*>(buffer);
    }

    // parse method const
    static const fx_lot_type_rules_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const fx_lot_type_rules_groups*>(buffer);
    }
};

#pragma pack(pop)
}
