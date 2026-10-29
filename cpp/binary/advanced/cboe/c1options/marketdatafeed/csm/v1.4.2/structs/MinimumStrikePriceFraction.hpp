#pragma once

#include <cstddef>
#include "../types/MinimumStrikePriceFractionExponent.hpp"
#include "../types/MinimumStrikePriceFractionMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

struct minimum_strike_price_fraction {

    csm_marketdatafeed::minimum_strike_price_fraction_exponent minimum_strike_price_fraction_exponent;
    csm_marketdatafeed::minimum_strike_price_fraction_mantissa minimum_strike_price_fraction_mantissa;

    // parse method
    static minimum_strike_price_fraction* parse(std::byte* buffer) {
        return reinterpret_cast<minimum_strike_price_fraction*>(buffer);
    }

    // parse method const
    static const minimum_strike_price_fraction* parse(const std::byte* buffer) {
        return reinterpret_cast<const minimum_strike_price_fraction*>(buffer);
    }
};

// layout verification
static_assert(offsetof(minimum_strike_price_fraction, minimum_strike_price_fraction_exponent) == 0, "unexpected offset of minimum_strike_price_fraction::minimum_strike_price_fraction_exponent");
static_assert(offsetof(minimum_strike_price_fraction, minimum_strike_price_fraction_mantissa) == 1, "unexpected offset of minimum_strike_price_fraction::minimum_strike_price_fraction_mantissa");
static_assert(sizeof(minimum_strike_price_fraction) == 5, "unexpected sizeof minimum_strike_price_fraction");

#pragma pack(pop)
}
