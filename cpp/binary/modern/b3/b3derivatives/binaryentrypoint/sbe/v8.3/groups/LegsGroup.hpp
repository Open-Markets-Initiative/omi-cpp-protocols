#pragma once

#include "../types/LegSymbol.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSide.hpp"
#include "../types/Padding1.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

struct LegsGroup {

    LegSymbol leg_symbol;
    LegRatioQty leg_ratio_qty;
    LegSide leg_side;
    Padding1 padding_1;

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
