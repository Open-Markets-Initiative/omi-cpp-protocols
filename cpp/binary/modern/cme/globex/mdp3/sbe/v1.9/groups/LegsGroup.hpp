#pragma once

#include "../types/LegSecurityId.hpp"
#include "../types/LegSide.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegPriceEx.hpp"
#include "../types/LegOptionDelta.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

struct LegsGroup {

    LegSecurityId leg_security_id;
    LegSide leg_side;
    LegRatioQty leg_ratio_qty;
    LegPriceEx leg_price_ex;
    LegOptionDelta leg_option_delta;

    // parse method
    static LegsGroup* parse(std::byte* buffer) {
        return reinterpret_cast<LegsGroup*>(buffer);
    }

    // parse method const
    static const LegsGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const LegsGroup*>(buffer);
    }
};

#pragma pack(pop)
}
