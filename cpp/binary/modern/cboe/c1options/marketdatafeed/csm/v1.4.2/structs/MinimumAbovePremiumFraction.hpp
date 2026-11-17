// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/MinimumAbovePremiumFraction.hpp
#pragma once

#include "../types/MinimumAbovePremiumFractionExponent.hpp"
#include "../types/MinimumAbovePremiumFractionMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct MinimumAbovePremiumFraction {

    MinimumAbovePremiumFractionExponent minimum_above_premium_fraction_exponent;
    MinimumAbovePremiumFractionMantissa minimum_above_premium_fraction_mantissa;

    // parse method
    static MinimumAbovePremiumFraction* parse(std::byte* buffer) {
        return reinterpret_cast<MinimumAbovePremiumFraction*>(buffer);
    }

    // parse method const
    static const MinimumAbovePremiumFraction* parse(const std::byte* buffer) {
        return reinterpret_cast<const MinimumAbovePremiumFraction*>(buffer);
    }
};

#pragma pack(pop)
}
