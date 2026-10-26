#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

struct collateral_market_value_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static collateral_market_value_groups* parse(std::byte* buffer) {
        return reinterpret_cast<collateral_market_value_groups*>(buffer);
    }

    // parse method const
    static const collateral_market_value_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const collateral_market_value_groups*>(buffer);
    }
};

#pragma pack(pop)
}
