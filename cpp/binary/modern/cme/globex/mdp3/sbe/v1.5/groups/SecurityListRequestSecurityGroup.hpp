#pragma once

#include "../types/SecurityGroup.hpp"

namespace cme::mdp3::v5 {

#pragma pack(push, 1)

struct SecurityListRequestSecurityGroup {

    SecurityGroup security_group;

    // parse method
    static SecurityListRequestSecurityGroup* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityListRequestSecurityGroup*>(buffer);
    }

    // parse method const
    static const SecurityListRequestSecurityGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityListRequestSecurityGroup*>(buffer);
    }
};

#pragma pack(pop)
}
