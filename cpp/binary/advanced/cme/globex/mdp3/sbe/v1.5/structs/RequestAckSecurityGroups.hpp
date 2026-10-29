#pragma once

#include <cstddef>
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;

#pragma pack(push, 1)

struct request_ack_security_groups {

    sbe_mdp3::group_size group_size;

    // parse method
    static request_ack_security_groups* parse(std::byte* buffer) {
        return reinterpret_cast<request_ack_security_groups*>(buffer);
    }

    // parse method const
    static const request_ack_security_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const request_ack_security_groups*>(buffer);
    }
};

#pragma pack(pop)
}
