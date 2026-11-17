// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/MinimumBelowPremiumFraction.hpp
#pragma once

#include "../types/MinimumBelowPremiumFractionExponent.hpp"
#include "../types/MinimumBelowPremiumFractionMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct MinimumBelowPremiumFraction {

    MinimumBelowPremiumFractionExponent minimum_below_premium_fraction_exponent;
    MinimumBelowPremiumFractionMantissa minimum_below_premium_fraction_mantissa;

    // parse method
    static MinimumBelowPremiumFraction* parse(std::byte* buffer) {
        return reinterpret_cast<MinimumBelowPremiumFraction*>(buffer);
    }

    // parse method const
    static const MinimumBelowPremiumFraction* parse(const std::byte* buffer) {
        return reinterpret_cast<const MinimumBelowPremiumFraction*>(buffer);
    }
};

#pragma pack(pop)
}
