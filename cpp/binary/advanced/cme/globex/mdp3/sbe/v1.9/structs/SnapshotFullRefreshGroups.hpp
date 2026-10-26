#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

#pragma pack(push, 1)

struct snapshot_full_refresh_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static snapshot_full_refresh_groups* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_full_refresh_groups*>(buffer);
    }

    // parse method const
    static const snapshot_full_refresh_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_full_refresh_groups*>(buffer);
    }
};

#pragma pack(pop)
}
