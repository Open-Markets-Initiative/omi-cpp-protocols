#pragma once

#include <cstddef>
#include "../types/MaxStrikePriceExponent.hpp"
#include "../types/MaxStrikePriceMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

struct max_strike_price {

    csm_marketdatafeed::max_strike_price_exponent max_strike_price_exponent;
    csm_marketdatafeed::max_strike_price_mantissa max_strike_price_mantissa;

    // parse method
    static max_strike_price* parse(std::byte* buffer) {
        return reinterpret_cast<max_strike_price*>(buffer);
    }

    // parse method const
    static const max_strike_price* parse(const std::byte* buffer) {
        return reinterpret_cast<const max_strike_price*>(buffer);
    }
};

// layout verification
static_assert(offsetof(max_strike_price, max_strike_price_exponent) == 0, "unexpected offset of max_strike_price::max_strike_price_exponent");
static_assert(offsetof(max_strike_price, max_strike_price_mantissa) == 1, "unexpected offset of max_strike_price::max_strike_price_mantissa");
static_assert(sizeof(max_strike_price) == 5, "unexpected sizeof max_strike_price");

#pragma pack(pop)
}
