#pragma once

#include <cstddef>

namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g {


// The side of the Unpaired Qty
struct UnpairedSide {

    static constexpr auto name = "Unpaired Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr UnpairedSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnpairedSide(const char &value)
     : value{ value } {}

    // get value of UnpairedSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
