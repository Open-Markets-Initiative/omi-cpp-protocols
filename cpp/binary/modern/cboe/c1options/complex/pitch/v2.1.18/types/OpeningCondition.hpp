#pragma once

#include <cstddef>

namespace cboe::c1options::complex::pitch::v2_1_18 {


// Not used for Complex series. Will contain zero value.
struct OpeningCondition {

    static constexpr auto name = "Opening Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OpeningCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpeningCondition(const char &value)
     : value{ value } {}

    // get value of OpeningCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
