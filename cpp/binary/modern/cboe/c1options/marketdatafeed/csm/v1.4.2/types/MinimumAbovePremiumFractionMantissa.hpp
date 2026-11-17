// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/MinimumAbovePremiumFractionMantissa.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// The multiple that premium can be when above the break point.
struct MinimumAbovePremiumFractionMantissa {

    static constexpr const char* name = "Minimum Above Premium Fraction Mantissa";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr MinimumAbovePremiumFractionMantissa()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinimumAbovePremiumFractionMantissa(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of MinimumAbovePremiumFractionMantissa field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
