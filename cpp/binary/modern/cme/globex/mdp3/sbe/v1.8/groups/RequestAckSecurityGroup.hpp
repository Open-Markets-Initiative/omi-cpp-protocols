#pragma once

#include "../types/SecurityGroup.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

struct RequestAckSecurityGroup {

    SecurityGroup security_group;

    // parse method
    static RequestAckSecurityGroup* parse(std::byte* buffer) {
        return reinterpret_cast<RequestAckSecurityGroup*>(buffer);
    }

    // parse method const
    static const RequestAckSecurityGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const RequestAckSecurityGroup*>(buffer);
    }
};

#pragma pack(pop)
}
