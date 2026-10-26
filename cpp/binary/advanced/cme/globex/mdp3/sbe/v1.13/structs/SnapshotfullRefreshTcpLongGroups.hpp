#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

struct snapshotfull_refresh_tcp_long_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static snapshotfull_refresh_tcp_long_groups* parse(std::byte* buffer) {
        return reinterpret_cast<snapshotfull_refresh_tcp_long_groups*>(buffer);
    }

    // parse method const
    static const snapshotfull_refresh_tcp_long_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshotfull_refresh_tcp_long_groups*>(buffer);
    }
};

#pragma pack(pop)
}
