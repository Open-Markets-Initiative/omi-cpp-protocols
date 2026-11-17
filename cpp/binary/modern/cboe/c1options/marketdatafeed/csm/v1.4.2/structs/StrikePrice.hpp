// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/StrikePrice.hpp
#pragma once

#include "../types/StrikePriceExponent.hpp"
#include "../types/StrikePriceMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct StrikePrice {

    StrikePriceExponent strike_price_exponent;
    StrikePriceMantissa strike_price_mantissa;

    // parse method
    static StrikePrice* parse(std::byte* buffer) {
        return reinterpret_cast<StrikePrice*>(buffer);
    }

    // parse method const
    static const StrikePrice* parse(const std::byte* buffer) {
        return reinterpret_cast<const StrikePrice*>(buffer);
    }
};

#pragma pack(pop)
}
