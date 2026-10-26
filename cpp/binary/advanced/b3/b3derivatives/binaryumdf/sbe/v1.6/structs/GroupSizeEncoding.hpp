#pragma once

#include <cstddef>
#include "../types/BlockLength.hpp"
#include "../types/NumInGroup.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_6;

#pragma pack(push, 1)

struct group_size_encoding {

    sbe_binaryumdf::block_length block_length;
    sbe_binaryumdf::num_in_group num_in_group;

    // parse method
    static group_size_encoding* parse(std::byte* buffer) {
        return reinterpret_cast<group_size_encoding*>(buffer);
    }

    // parse method const
    static const group_size_encoding* parse(const std::byte* buffer) {
        return reinterpret_cast<const group_size_encoding*>(buffer);
    }
};

// layout verification
static_assert(offsetof(group_size_encoding, block_length) == 0, "unexpected offset of group_size_encoding::block_length");
static_assert(offsetof(group_size_encoding, num_in_group) == 2, "unexpected offset of group_size_encoding::num_in_group");
static_assert(sizeof(group_size_encoding) == 3, "unexpected sizeof group_size_encoding");

#pragma pack(pop)
}
