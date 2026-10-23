#pragma once

#include <cstddef>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Populated if the Statistic Type is 2 or 3.
struct OpeningClosingPriceIndicator {

    static constexpr auto name = "Opening Closing Price Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OpeningClosingPriceIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpeningClosingPriceIndicator(const char &value)
     : value{ value } {}

    // get value of OpeningClosingPriceIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
