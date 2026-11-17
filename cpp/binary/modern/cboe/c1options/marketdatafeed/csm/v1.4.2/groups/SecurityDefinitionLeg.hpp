// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: groups/SecurityDefinitionLeg.hpp
#pragma once

#include "../types/LegRatioQty.hpp"
#include "../types/LegSecurityId.hpp"
#include "../types/LegSide.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct SecurityDefinitionLeg {

    LegRatioQty leg_ratio_qty;
    LegSecurityId leg_security_id;
    LegSide leg_side;

    // parse method
    static SecurityDefinitionLeg* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityDefinitionLeg*>(buffer);
    }

    // parse method const
    static const SecurityDefinitionLeg* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityDefinitionLeg*>(buffer);
    }
};

#pragma pack(pop)
}
