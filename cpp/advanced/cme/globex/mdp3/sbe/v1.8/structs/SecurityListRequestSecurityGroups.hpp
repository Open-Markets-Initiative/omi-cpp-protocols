#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

#pragma pack(push, 1)

struct security_list_request_security_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static security_list_request_security_groups* parse(std::byte* buffer) {
        return reinterpret_cast<security_list_request_security_groups*>(buffer);
    }

    // parse method const
    static const security_list_request_security_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_list_request_security_groups*>(buffer);
    }
};

#pragma pack(pop)
}
