#pragma once

#include <cstddef>
#include "../types/MinimumAbovePremiumFractionExponent.hpp"
#include "../types/MinimumAbovePremiumFractionMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

struct minimum_above_premium_fraction {

    csm_marketdatafeed::minimum_above_premium_fraction_exponent minimum_above_premium_fraction_exponent;
    csm_marketdatafeed::minimum_above_premium_fraction_mantissa minimum_above_premium_fraction_mantissa;

    // parse method
    static minimum_above_premium_fraction* parse(std::byte* buffer) {
        return reinterpret_cast<minimum_above_premium_fraction*>(buffer);
    }

    // parse method const
    static const minimum_above_premium_fraction* parse(const std::byte* buffer) {
        return reinterpret_cast<const minimum_above_premium_fraction*>(buffer);
    }
};

// layout verification
static_assert(offsetof(minimum_above_premium_fraction, minimum_above_premium_fraction_exponent) == 0, "unexpected offset of minimum_above_premium_fraction::minimum_above_premium_fraction_exponent");
static_assert(offsetof(minimum_above_premium_fraction, minimum_above_premium_fraction_mantissa) == 1, "unexpected offset of minimum_above_premium_fraction::minimum_above_premium_fraction_mantissa");
static_assert(sizeof(minimum_above_premium_fraction) == 5, "unexpected sizeof minimum_above_premium_fraction");

#pragma pack(pop)
}
