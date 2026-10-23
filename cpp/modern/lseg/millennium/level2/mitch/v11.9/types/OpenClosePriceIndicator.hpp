#pragma once

#include <cstddef>

namespace lseg::millennium::level2::mitch::v11_9 {


// 
struct OpenClosePriceIndicator {

    static constexpr auto name = "Open Close Price Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OpenClosePriceIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenClosePriceIndicator(const char &value)
     : value{ value } {}

    // get value of OpenClosePriceIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
