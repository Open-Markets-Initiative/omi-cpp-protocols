#pragma once

#include "../types/LegSymbol.hpp"
#include "../types/Pad4.hpp"
#include "../types/LegSecurityId.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSide.hpp"
#include "../types/Pad3.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

#pragma pack(push, 1)

struct InstrmtLegGrpComp {

    LegSymbol leg_symbol;
    Pad4 pad4;
    LegSecurityId leg_security_id;
    LegRatioQty leg_ratio_qty;
    LegSide leg_side;
    Pad3 pad3;

    // parse method
    static InstrmtLegGrpComp* parse(std::byte* buffer) {
        return reinterpret_cast<InstrmtLegGrpComp*>(buffer);
    }

    // parse method const
    static const InstrmtLegGrpComp* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrmtLegGrpComp*>(buffer);
    }
};

#pragma pack(pop)
}
