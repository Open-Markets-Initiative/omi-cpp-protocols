#pragma once

#include <cstddef>
#include "../types/BlockLength.hpp"
#include "../types/NumInGroup.hpp"

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

#pragma pack(push, 1)

struct group_size {

    sbe_mdp3::block_length block_length;
    sbe_mdp3::num_in_group num_in_group;

    // parse method
    static group_size* parse(std::byte* buffer) {
        return reinterpret_cast<group_size*>(buffer);
    }

    // parse method const
    static const group_size* parse(const std::byte* buffer) {
        return reinterpret_cast<const group_size*>(buffer);
    }
};

// layout verification
static_assert(offsetof(group_size, block_length) == 0, "unexpected offset of group_size::block_length");
static_assert(offsetof(group_size, num_in_group) == 2, "unexpected offset of group_size::num_in_group");
static_assert(sizeof(group_size) == 3, "unexpected sizeof group_size");

#pragma pack(pop)
}
