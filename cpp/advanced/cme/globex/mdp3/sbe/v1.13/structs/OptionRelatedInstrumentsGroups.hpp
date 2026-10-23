#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

struct option_related_instruments_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static option_related_instruments_groups* parse(std::byte* buffer) {
        return reinterpret_cast<option_related_instruments_groups*>(buffer);
    }

    // parse method const
    static const option_related_instruments_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const option_related_instruments_groups*>(buffer);
    }
};

#pragma pack(pop)
}
