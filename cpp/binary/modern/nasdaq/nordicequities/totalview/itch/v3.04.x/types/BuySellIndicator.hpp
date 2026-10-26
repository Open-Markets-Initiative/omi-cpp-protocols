#pragma once

#include <cstddef>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {


// The type of order being added
struct BuySellIndicator {

    static constexpr auto name = "Buy Sell Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr BuySellIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BuySellIndicator(const char &value)
     : value{ value } {}

    // get value of BuySellIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
