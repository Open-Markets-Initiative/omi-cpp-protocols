// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/MinimumBelowPremiumFractionExponent.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// The multiple that premium can be when below the break point.
struct MinimumBelowPremiumFractionExponent {

    static constexpr auto name = "Minimum Below Premium Fraction Exponent";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr MinimumBelowPremiumFractionExponent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinimumBelowPremiumFractionExponent(const std::int8_t &value)
     : value{ value } {}

    // get value of MinimumBelowPremiumFractionExponent field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
