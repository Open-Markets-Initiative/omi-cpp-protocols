#pragma once

#include "../types/LegSecurityId.hpp"
#include "../types/LegSide.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegPrice.hpp"
#include "../types/LegOptionDelta.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct LegsGroup {

    LegSecurityId leg_security_id;
    LegSide leg_side;
    LegRatioQty leg_ratio_qty;
    LegPrice leg_price;
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
