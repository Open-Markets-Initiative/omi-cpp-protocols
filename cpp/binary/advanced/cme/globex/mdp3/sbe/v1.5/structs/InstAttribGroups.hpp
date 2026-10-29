#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;

#pragma pack(push, 1)

struct inst_attrib_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static inst_attrib_groups* parse(std::byte* buffer) {
        return reinterpret_cast<inst_attrib_groups*>(buffer);
    }

    // parse method const
    static const inst_attrib_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const inst_attrib_groups*>(buffer);
    }
};

#pragma pack(pop)
}
