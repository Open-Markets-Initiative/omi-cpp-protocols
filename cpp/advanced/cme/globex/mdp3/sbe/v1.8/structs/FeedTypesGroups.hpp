#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

#pragma pack(push, 1)

struct feed_types_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static feed_types_groups* parse(std::byte* buffer) {
        return reinterpret_cast<feed_types_groups*>(buffer);
    }

    // parse method const
    static const feed_types_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const feed_types_groups*>(buffer);
    }
};

#pragma pack(pop)
}
