#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

struct trading_sessions_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static trading_sessions_groups* parse(std::byte* buffer) {
        return reinterpret_cast<trading_sessions_groups*>(buffer);
    }

    // parse method const
    static const trading_sessions_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const trading_sessions_groups*>(buffer);
    }
};

#pragma pack(pop)
}
