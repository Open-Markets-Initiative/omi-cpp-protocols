#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

#pragma pack(push, 1)

struct security_status_request_related_symbol_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static security_status_request_related_symbol_groups* parse(std::byte* buffer) {
        return reinterpret_cast<security_status_request_related_symbol_groups*>(buffer);
    }

    // parse method const
    static const security_status_request_related_symbol_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_status_request_related_symbol_groups*>(buffer);
    }
};

#pragma pack(pop)
}
