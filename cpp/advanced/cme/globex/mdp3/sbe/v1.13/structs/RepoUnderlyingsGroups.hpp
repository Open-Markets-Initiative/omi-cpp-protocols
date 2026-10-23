#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

struct repo_underlyings_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static repo_underlyings_groups* parse(std::byte* buffer) {
        return reinterpret_cast<repo_underlyings_groups*>(buffer);
    }

    // parse method const
    static const repo_underlyings_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const repo_underlyings_groups*>(buffer);
    }
};

#pragma pack(pop)
}
