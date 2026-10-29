#pragma once

#include <cstddef>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// The currency in which all Futures Instruments of the Futures Product will trade
struct Currency {

    static constexpr auto name = "Currency";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Currency()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Currency(const char &value)
     : value{ value } {}

    // get value of Currency field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
