#pragma once

#include <cstddef>
#include "../types/PremiumBreakPointExponent.hpp"
#include "../types/PremiumBreakPointMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

struct premium_break_point {

    csm_marketdatafeed::premium_break_point_exponent premium_break_point_exponent;
    csm_marketdatafeed::premium_break_point_mantissa premium_break_point_mantissa;

    // parse method
    static premium_break_point* parse(std::byte* buffer) {
        return reinterpret_cast<premium_break_point*>(buffer);
    }

    // parse method const
    static const premium_break_point* parse(const std::byte* buffer) {
        return reinterpret_cast<const premium_break_point*>(buffer);
    }
};

// layout verification
static_assert(offsetof(premium_break_point, premium_break_point_exponent) == 0, "unexpected offset of premium_break_point::premium_break_point_exponent");
static_assert(offsetof(premium_break_point, premium_break_point_mantissa) == 1, "unexpected offset of premium_break_point::premium_break_point_mantissa");
static_assert(sizeof(premium_break_point) == 5, "unexpected sizeof premium_break_point");

#pragma pack(pop)
}
