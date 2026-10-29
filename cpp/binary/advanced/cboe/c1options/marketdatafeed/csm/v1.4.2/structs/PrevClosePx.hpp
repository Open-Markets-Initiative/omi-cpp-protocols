#pragma once

#include <cstddef>
#include "../types/PrevClosePxExponent.hpp"
#include "../types/PrevClosePxMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

struct prev_close_px {

    csm_marketdatafeed::prev_close_px_exponent prev_close_px_exponent;
    csm_marketdatafeed::prev_close_px_mantissa prev_close_px_mantissa;

    // parse method
    static prev_close_px* parse(std::byte* buffer) {
        return reinterpret_cast<prev_close_px*>(buffer);
    }

    // parse method const
    static const prev_close_px* parse(const std::byte* buffer) {
        return reinterpret_cast<const prev_close_px*>(buffer);
    }
};

// layout verification
static_assert(offsetof(prev_close_px, prev_close_px_exponent) == 0, "unexpected offset of prev_close_px::prev_close_px_exponent");
static_assert(offsetof(prev_close_px, prev_close_px_mantissa) == 1, "unexpected offset of prev_close_px::prev_close_px_mantissa");
static_assert(sizeof(prev_close_px) == 5, "unexpected sizeof prev_close_px");

#pragma pack(pop)
}
