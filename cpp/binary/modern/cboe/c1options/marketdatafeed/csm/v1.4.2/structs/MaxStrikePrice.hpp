// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/MaxStrikePrice.hpp
#pragma once

#include "../types/MaxStrikePriceExponent.hpp"
#include "../types/MaxStrikePriceMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct MaxStrikePrice {

    MaxStrikePriceExponent max_strike_price_exponent;
    MaxStrikePriceMantissa max_strike_price_mantissa;

    // parse method
    static MaxStrikePrice* parse(std::byte* buffer) {
        return reinterpret_cast<MaxStrikePrice*>(buffer);
    }

    // parse method const
    static const MaxStrikePrice* parse(const std::byte* buffer) {
        return reinterpret_cast<const MaxStrikePrice*>(buffer);
    }
};

#pragma pack(pop)
}
