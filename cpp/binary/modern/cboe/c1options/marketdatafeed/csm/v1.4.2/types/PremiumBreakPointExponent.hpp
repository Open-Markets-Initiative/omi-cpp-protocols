// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/PremiumBreakPointExponent.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// The premium price where above and below fractions take effect.
struct PremiumBreakPointExponent {

    static constexpr auto name = "Premium Break Point Exponent";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr PremiumBreakPointExponent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PremiumBreakPointExponent(const std::int8_t &value)
     : value{ value } {}

    // get value of PremiumBreakPointExponent field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
