// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/PremiumBreakPoint.hpp
#pragma once

#include "../types/PremiumBreakPointExponent.hpp"
#include "../types/PremiumBreakPointMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct PremiumBreakPoint {

    PremiumBreakPointExponent premium_break_point_exponent;
    PremiumBreakPointMantissa premium_break_point_mantissa;

    // parse method
    static PremiumBreakPoint* parse(std::byte* buffer) {
        return reinterpret_cast<PremiumBreakPoint*>(buffer);
    }

    // parse method const
    static const PremiumBreakPoint* parse(const std::byte* buffer) {
        return reinterpret_cast<const PremiumBreakPoint*>(buffer);
    }
};

#pragma pack(pop)
}
