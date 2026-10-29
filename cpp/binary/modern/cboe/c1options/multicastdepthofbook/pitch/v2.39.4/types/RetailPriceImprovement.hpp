#pragma once

#include <cstddef>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {


// Retail price improvement value
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
