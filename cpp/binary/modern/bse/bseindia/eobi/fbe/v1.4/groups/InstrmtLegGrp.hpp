#pragma once

#include "../types/LegSecurityId.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSide.hpp"
#include "../types/Pad3.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

struct InstrmtLegGrp {

    LegSecurityId leg_security_id;
    LegRatioQty leg_ratio_qty;
    LegSide leg_side;
    Pad3 pad_3;

    // parse method
    static InstrmtLegGrp* parse(std::byte* buffer) {
        return reinterpret_cast<InstrmtLegGrp*>(buffer);
    }

    // parse method const
    static const InstrmtLegGrp* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrmtLegGrp*>(buffer);
    }
};

#pragma pack(pop)
}
