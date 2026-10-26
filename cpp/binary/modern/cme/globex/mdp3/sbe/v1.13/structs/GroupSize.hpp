#pragma once

#include "../types/BlockLength.hpp"
#include "../types/NumInGroup.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct GroupSize {

    BlockLength block_length;
    NumInGroup num_in_group;

    // parse method
    static GroupSize* parse(std::byte* buffer) {
        return reinterpret_cast<GroupSize*>(buffer);
    }

    // parse method const
    static const GroupSize* parse(const std::byte* buffer) {
        return reinterpret_cast<const GroupSize*>(buffer);
    }
};

#pragma pack(pop)
}
