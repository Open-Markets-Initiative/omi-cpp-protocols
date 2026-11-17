// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/MinimumStrikePriceFractionMantissa.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// The multiple by which the strike price can be
struct MinimumStrikePriceFractionMantissa {

    static constexpr const char* name = "Minimum Strike Price Fraction Mantissa";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr MinimumStrikePriceFractionMantissa()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinimumStrikePriceFractionMantissa(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of MinimumStrikePriceFractionMantissa field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
