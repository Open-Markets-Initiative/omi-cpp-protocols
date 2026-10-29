#pragma once

#include <cstddef>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {


// "B" = Buy Side RPI "S" = Sell Side RPI "A" = Buy & Sell RPI
struct RetailPriceImprovement {

    static constexpr auto name = "Retail Price Improvement";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr RetailPriceImprovement()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RetailPriceImprovement(const char &value)
     : value{ value } {}

    // get value of RetailPriceImprovement field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
