// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/UnderlyingPx.hpp
#pragma once

#include "../types/UnderlyingPxExponent.hpp"
#include "../types/UnderlyingPxMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct UnderlyingPx {

    UnderlyingPxExponent underlying_px_exponent;
    UnderlyingPxMantissa underlying_px_mantissa;

    // parse method
    static UnderlyingPx* parse(std::byte* buffer) {
        return reinterpret_cast<UnderlyingPx*>(buffer);
    }

    // parse method const
    static const UnderlyingPx* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnderlyingPx*>(buffer);
    }
};

#pragma pack(pop)
}
