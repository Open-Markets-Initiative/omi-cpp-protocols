#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;

#pragma pack(push, 1)

struct incremental_refresh_daily_statistics_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static incremental_refresh_daily_statistics_groups* parse(std::byte* buffer) {
        return reinterpret_cast<incremental_refresh_daily_statistics_groups*>(buffer);
    }

    // parse method const
    static const incremental_refresh_daily_statistics_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const incremental_refresh_daily_statistics_groups*>(buffer);
    }
};

#pragma pack(pop)
}
