// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/MinimumStrikePriceFraction.hpp
#pragma once

#include "../types/MinimumStrikePriceFractionExponent.hpp"
#include "../types/MinimumStrikePriceFractionMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct MinimumStrikePriceFraction {

    MinimumStrikePriceFractionExponent minimum_strike_price_fraction_exponent;
    MinimumStrikePriceFractionMantissa minimum_strike_price_fraction_mantissa;

    // parse method
    static MinimumStrikePriceFraction* parse(std::byte* buffer) {
        return reinterpret_cast<MinimumStrikePriceFraction*>(buffer);
    }

    // parse method const
    static const MinimumStrikePriceFraction* parse(const std::byte* buffer) {
        return reinterpret_cast<const MinimumStrikePriceFraction*>(buffer);
    }
};

#pragma pack(pop)
}
