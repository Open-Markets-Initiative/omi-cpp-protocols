#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;

#pragma pack(push, 1)

struct lot_type_rules_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static lot_type_rules_groups* parse(std::byte* buffer) {
        return reinterpret_cast<lot_type_rules_groups*>(buffer);
    }

    // parse method const
    static const lot_type_rules_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const lot_type_rules_groups*>(buffer);
    }
};

#pragma pack(pop)
}
