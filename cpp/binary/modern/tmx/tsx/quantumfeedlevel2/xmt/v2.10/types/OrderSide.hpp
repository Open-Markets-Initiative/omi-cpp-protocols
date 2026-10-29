#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// Market Side Of An Order
struct OrderSide {

    static constexpr auto name = "Order Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OrderSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderSide(const char &value)
     : value{ value } {}

    // get value of OrderSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
