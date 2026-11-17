// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/MinimumStrikePriceFractionExponent.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// The multiple by which the strike price can be
struct MinimumStrikePriceFractionExponent {

    static constexpr auto name = "Minimum Strike Price Fraction Exponent";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr MinimumStrikePriceFractionExponent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinimumStrikePriceFractionExponent(const std::int8_t &value)
     : value{ value } {}

    // get value of MinimumStrikePriceFractionExponent field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
