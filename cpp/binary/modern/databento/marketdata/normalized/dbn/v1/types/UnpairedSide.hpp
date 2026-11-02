#pragma once

#include <cstddef>

namespace databento::marketdata::normalized::dbn::v1 {


// Reserved for future use
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
