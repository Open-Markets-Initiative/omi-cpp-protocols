// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/StrikePriceExponent.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// First byte is the exponent, last 4 bytes are the mantissa. This field is required for options
struct StrikePriceExponent {

    static constexpr auto name = "Strike Price Exponent";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr StrikePriceExponent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrikePriceExponent(const std::int8_t &value)
     : value{ value } {}

    // get value of StrikePriceExponent field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
