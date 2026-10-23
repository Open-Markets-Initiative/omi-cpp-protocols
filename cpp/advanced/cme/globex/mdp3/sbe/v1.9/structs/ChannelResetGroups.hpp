#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

#pragma pack(push, 1)

struct channel_reset_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static channel_reset_groups* parse(std::byte* buffer) {
        return reinterpret_cast<channel_reset_groups*>(buffer);
    }

    // parse method const
    static const channel_reset_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const channel_reset_groups*>(buffer);
    }
};

#pragma pack(pop)
}
