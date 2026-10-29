#pragma once

#include <cstddef>
#include "../types/StrikePriceExponent.hpp"
#include "../types/StrikePriceMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

struct strike_price {

    csm_marketdatafeed::strike_price_exponent strike_price_exponent;
    csm_marketdatafeed::strike_price_mantissa strike_price_mantissa;

    // parse method
    static strike_price* parse(std::byte* buffer) {
        return reinterpret_cast<strike_price*>(buffer);
    }

    // parse method const
    static const strike_price* parse(const std::byte* buffer) {
        return reinterpret_cast<const strike_price*>(buffer);
    }
};

// layout verification
static_assert(offsetof(strike_price, strike_price_exponent) == 0, "unexpected offset of strike_price::strike_price_exponent");
static_assert(offsetof(strike_price, strike_price_mantissa) == 1, "unexpected offset of strike_price::strike_price_mantissa");
static_assert(sizeof(strike_price) == 5, "unexpected sizeof strike_price");

#pragma pack(pop)
}
