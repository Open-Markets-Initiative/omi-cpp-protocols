#pragma once

#include <cstddef>
#include "../types/EopExponent.hpp"
#include "../types/EopMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

struct eop {

    csm_marketdatafeed::eop_exponent eop_exponent;
    csm_marketdatafeed::eop_mantissa eop_mantissa;

    // parse method
    static eop* parse(std::byte* buffer) {
        return reinterpret_cast<eop*>(buffer);
    }

    // parse method const
    static const eop* parse(const std::byte* buffer) {
        return reinterpret_cast<const eop*>(buffer);
    }
};

// layout verification
static_assert(offsetof(eop, eop_exponent) == 0, "unexpected offset of eop::eop_exponent");
static_assert(offsetof(eop, eop_mantissa) == 1, "unexpected offset of eop::eop_mantissa");
static_assert(sizeof(eop) == 5, "unexpected sizeof eop");

#pragma pack(pop)
}
