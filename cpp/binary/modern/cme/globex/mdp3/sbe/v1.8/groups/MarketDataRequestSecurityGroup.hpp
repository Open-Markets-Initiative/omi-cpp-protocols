// Cme.Globex.Mdp3.Sbe.v1.8: groups/MarketDataRequestSecurityGroup.hpp
#pragma once

#include "../types/SecurityGroup.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

struct MarketDataRequestSecurityGroup {

    SecurityGroup security_group;

    // parse method
    static MarketDataRequestSecurityGroup* parse(std::byte* buffer) {
        return reinterpret_cast<MarketDataRequestSecurityGroup*>(buffer);
    }

    // parse method const
    static const MarketDataRequestSecurityGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketDataRequestSecurityGroup*>(buffer);
    }
};

#pragma pack(pop)
}
