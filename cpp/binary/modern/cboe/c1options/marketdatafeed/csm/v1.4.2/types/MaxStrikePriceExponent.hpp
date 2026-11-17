// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/MaxStrikePriceExponent.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// The maximum allowable strike price.
struct MaxStrikePriceExponent {

    static constexpr auto name = "Max Strike Price Exponent";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr MaxStrikePriceExponent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaxStrikePriceExponent(const std::int8_t &value)
     : value{ value } {}

    // get value of MaxStrikePriceExponent field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
