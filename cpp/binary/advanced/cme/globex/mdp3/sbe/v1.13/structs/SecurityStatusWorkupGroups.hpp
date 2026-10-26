#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

struct security_status_workup_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static security_status_workup_groups* parse(std::byte* buffer) {
        return reinterpret_cast<security_status_workup_groups*>(buffer);
    }

    // parse method const
    static const security_status_workup_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_status_workup_groups*>(buffer);
    }
};

#pragma pack(pop)
}
