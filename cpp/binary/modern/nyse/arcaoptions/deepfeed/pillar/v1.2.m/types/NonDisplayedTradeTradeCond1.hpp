#pragma once

#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Settlement related conditions.
struct NonDisplayedTradeTradeCond1 {

    static constexpr auto name = "Non Displayed Trade Trade Cond 1";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr NonDisplayedTradeTradeCond1()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NonDisplayedTradeTradeCond1(const char &value)
     : value{ value } {}

    // get value of NonDisplayedTradeTradeCond1 field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
