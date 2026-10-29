#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;

#pragma pack(push, 1)

struct related_sym_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static related_sym_groups* parse(std::byte* buffer) {
        return reinterpret_cast<related_sym_groups*>(buffer);
    }

    // parse method const
    static const related_sym_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const related_sym_groups*>(buffer);
    }
};

#pragma pack(pop)
}
