// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/MinimumBelowPremiumFractionMantissa.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// The multiple that premium can be when below the break point.
struct MinimumBelowPremiumFractionMantissa {

    static constexpr const char* name = "Minimum Below Premium Fraction Mantissa";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr MinimumBelowPremiumFractionMantissa()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinimumBelowPremiumFractionMantissa(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of MinimumBelowPremiumFractionMantissa field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
