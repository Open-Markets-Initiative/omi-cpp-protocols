#pragma once

#include "../types/LegSecurityId.hpp"
#include "../types/LegSide.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegPrice.hpp"
#include "../types/LegOptionDelta.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

struct LegacyLegsGroup {

    LegSecurityId leg_security_id;
    LegSide leg_side;
    LegRatioQty leg_ratio_qty;
    LegPrice leg_price;
    LegOptionDelta leg_option_delta;

    // parse method
    static LegacyLegsGroup* parse(std::byte* buffer) {
        return reinterpret_cast<LegacyLegsGroup*>(buffer);
    }

    // parse method const
    static const LegacyLegsGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const LegacyLegsGroup*>(buffer);
    }
};

#pragma pack(pop)
}
