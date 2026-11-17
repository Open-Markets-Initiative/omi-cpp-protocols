// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/Eop.hpp
#pragma once

#include "../types/EopExponent.hpp"
#include "../types/EopMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct Eop {

    EopExponent eop_exponent;
    EopMantissa eop_mantissa;

    // parse method
    static Eop* parse(std::byte* buffer) {
        return reinterpret_cast<Eop*>(buffer);
    }

    // parse method const
    static const Eop* parse(const std::byte* buffer) {
        return reinterpret_cast<const Eop*>(buffer);
    }
};

#pragma pack(pop)
}
