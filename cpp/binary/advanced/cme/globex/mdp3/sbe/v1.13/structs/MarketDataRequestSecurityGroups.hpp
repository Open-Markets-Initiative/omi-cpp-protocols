#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

struct market_data_request_security_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static market_data_request_security_groups* parse(std::byte* buffer) {
        return reinterpret_cast<market_data_request_security_groups*>(buffer);
    }

    // parse method const
    static const market_data_request_security_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const market_data_request_security_groups*>(buffer);
    }
};

#pragma pack(pop)
}
