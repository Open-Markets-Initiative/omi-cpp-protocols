#pragma once

#include "../types/LegRatio.hpp"
#include "../types/LegSymbol.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

#pragma pack(push, 1)

struct FutureLeg {

    LegRatio leg_ratio;
    LegSymbol leg_symbol;

    // parse method
    static FutureLeg* parse(std::byte* buffer) {
        return reinterpret_cast<FutureLeg*>(buffer);
    }

    // parse method const
    static const FutureLeg* parse(const std::byte* buffer) {
        return reinterpret_cast<const FutureLeg*>(buffer);
    }
};

#pragma pack(pop)
}
