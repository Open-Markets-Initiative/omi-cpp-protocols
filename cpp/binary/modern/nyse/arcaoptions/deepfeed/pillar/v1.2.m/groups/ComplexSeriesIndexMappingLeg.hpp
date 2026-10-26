#pragma once

#include "../types/SymbolIndex.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSide.hpp"
#include "../types/LegSecurityType.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

struct ComplexSeriesIndexMappingLeg {

    SymbolIndex symbol_index;
    LegRatioQty leg_ratio_qty;
    LegSide leg_side;
    LegSecurityType leg_security_type;

    // parse method
    static ComplexSeriesIndexMappingLeg* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexSeriesIndexMappingLeg*>(buffer);
    }

    // parse method const
    static const ComplexSeriesIndexMappingLeg* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexSeriesIndexMappingLeg*>(buffer);
    }
};

#pragma pack(pop)
}
