#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

#pragma pack(push, 1)

struct events_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static events_groups* parse(std::byte* buffer) {
        return reinterpret_cast<events_groups*>(buffer);
    }

    // parse method const
    static const events_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const events_groups*>(buffer);
    }
};

#pragma pack(pop)
}
