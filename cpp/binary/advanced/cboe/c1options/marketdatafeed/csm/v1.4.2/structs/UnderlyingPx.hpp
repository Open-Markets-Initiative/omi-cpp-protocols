#pragma once

#include <cstddef>
#include "../types/UnderlyingPxExponent.hpp"
#include "../types/UnderlyingPxMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

struct underlying_px {

    csm_marketdatafeed::underlying_px_exponent underlying_px_exponent;
    csm_marketdatafeed::underlying_px_mantissa underlying_px_mantissa;

    // parse method
    static underlying_px* parse(std::byte* buffer) {
        return reinterpret_cast<underlying_px*>(buffer);
    }

    // parse method const
    static const underlying_px* parse(const std::byte* buffer) {
        return reinterpret_cast<const underlying_px*>(buffer);
    }
};

// layout verification
static_assert(offsetof(underlying_px, underlying_px_exponent) == 0, "unexpected offset of underlying_px::underlying_px_exponent");
static_assert(offsetof(underlying_px, underlying_px_mantissa) == 1, "unexpected offset of underlying_px::underlying_px_mantissa");
static_assert(sizeof(underlying_px) == 5, "unexpected sizeof underlying_px");

#pragma pack(pop)
}
