#pragma once

#include "../types/SecurityGroup.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct SecurityStatusRequestSecurityGroup {

    SecurityGroup security_group;

    // parse method
    static SecurityStatusRequestSecurityGroup* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityStatusRequestSecurityGroup*>(buffer);
    }

    // parse method const
    static const SecurityStatusRequestSecurityGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityStatusRequestSecurityGroup*>(buffer);
    }
};

#pragma pack(pop)
}
