#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Identifies the applicable tick size for a symbol
struct MinimumPriceIncrementIndicator {

    static constexpr auto name = "Minimum Price Increment Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MinimumPriceIncrementIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinimumPriceIncrementIndicator(const char &value)
     : value{ value } {}

    // get value of MinimumPriceIncrementIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
