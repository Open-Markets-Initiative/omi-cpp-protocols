#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

#pragma pack(push, 1)

struct incremental_refresh_limits_banding_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static incremental_refresh_limits_banding_groups* parse(std::byte* buffer) {
        return reinterpret_cast<incremental_refresh_limits_banding_groups*>(buffer);
    }

    // parse method const
    static const incremental_refresh_limits_banding_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const incremental_refresh_limits_banding_groups*>(buffer);
    }
};

#pragma pack(pop)
}
