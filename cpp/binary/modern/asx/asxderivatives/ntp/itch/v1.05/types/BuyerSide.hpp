#pragma once

#include <cstddef>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Type of order
struct BuyerSide {

    static constexpr auto name = "Buyer Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr BuyerSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BuyerSide(const char &value)
     : value{ value } {}

    // get value of BuyerSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
