// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/PrevClosePx.hpp
#pragma once

#include "../types/PrevClosePxExponent.hpp"
#include "../types/PrevClosePxMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct PrevClosePx {

    PrevClosePxExponent prev_close_px_exponent;
    PrevClosePxMantissa prev_close_px_mantissa;

    // parse method
    static PrevClosePx* parse(std::byte* buffer) {
        return reinterpret_cast<PrevClosePx*>(buffer);
    }

    // parse method const
    static const PrevClosePx* parse(const std::byte* buffer) {
        return reinterpret_cast<const PrevClosePx*>(buffer);
    }
};

#pragma pack(pop)
}
