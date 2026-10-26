#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

struct snapshot_refresh_top_orders_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static snapshot_refresh_top_orders_groups* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_refresh_top_orders_groups*>(buffer);
    }

    // parse method const
    static const snapshot_refresh_top_orders_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_refresh_top_orders_groups*>(buffer);
    }
};

#pragma pack(pop)
}
