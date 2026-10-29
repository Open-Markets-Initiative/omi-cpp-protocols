#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// An Indicator For Bypass Crosses Which Can Be Printed Outside Of The Protected Nbbo And Are Not Subject To Cross Interference
struct Bypass {

    static constexpr auto name = "Bypass";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Bypass()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Bypass(const char &value)
     : value{ value } {}

    // get value of Bypass field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
