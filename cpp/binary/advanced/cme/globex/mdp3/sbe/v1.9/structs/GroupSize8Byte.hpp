#pragma once

#include <cstddef>
#include "../types/BlockLength.hpp"
#include "../types/Padding5.hpp"
#include "../types/NumInGroup.hpp"

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

#pragma pack(push, 1)

struct group_size_8_byte {

    sbe_mdp3::block_length block_length;
    sbe_mdp3::padding_5 padding_5;
    sbe_mdp3::num_in_group num_in_group;

    // parse method
    static group_size_8_byte* parse(std::byte* buffer) {
        return reinterpret_cast<group_size_8_byte*>(buffer);
    }

    // parse method const
    static const group_size_8_byte* parse(const std::byte* buffer) {
        return reinterpret_cast<const group_size_8_byte*>(buffer);
    }
};

// layout verification
static_assert(offsetof(group_size_8_byte, block_length) == 0, "unexpected offset of group_size_8_byte::block_length");
static_assert(offsetof(group_size_8_byte, padding_5) == 2, "unexpected offset of group_size_8_byte::padding_5");
static_assert(offsetof(group_size_8_byte, num_in_group) == 7, "unexpected offset of group_size_8_byte::num_in_group");
static_assert(sizeof(group_size_8_byte) == 8, "unexpected sizeof group_size_8_byte");

#pragma pack(pop)
}
