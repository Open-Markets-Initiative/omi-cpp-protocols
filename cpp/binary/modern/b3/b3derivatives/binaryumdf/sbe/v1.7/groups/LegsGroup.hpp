#pragma once

#include "../types/LegSecurityId.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSecurityType.hpp"
#include "../types/LegSide.hpp"
#include "../types/LegSymbol.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

#pragma pack(push, 1)

struct LegsGroup {

    LegSecurityId leg_security_id;
    LegRatioQty leg_ratio_qty;
    LegSecurityType leg_security_type;
    LegSide leg_side;
    LegSymbol leg_symbol;

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
