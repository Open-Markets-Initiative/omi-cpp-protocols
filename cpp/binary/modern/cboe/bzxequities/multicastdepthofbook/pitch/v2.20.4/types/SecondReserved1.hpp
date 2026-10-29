#pragma once

#include <cstddef>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {


// Reserved
struct SecondReserved1 {

    static constexpr auto name = "Second Reserved 1";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecondReserved1()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecondReserved1(const char &value)
     : value{ value } {}

    // get value of SecondReserved1 field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
