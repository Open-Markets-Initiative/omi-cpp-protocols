#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;

#pragma pack(push, 1)

struct legacy_legs_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static legacy_legs_groups* parse(std::byte* buffer) {
        return reinterpret_cast<legacy_legs_groups*>(buffer);
    }

    // parse method const
    static const legacy_legs_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const legacy_legs_groups*>(buffer);
    }
};

#pragma pack(pop)
}
