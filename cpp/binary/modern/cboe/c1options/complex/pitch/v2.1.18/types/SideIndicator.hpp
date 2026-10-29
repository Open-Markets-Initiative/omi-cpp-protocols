#pragma once

#include <cstddef>

namespace cboe::c1options::complex::pitch::v2_1_18 {


// Order Side
struct SideIndicator {

    static constexpr auto name = "Side Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SideIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SideIndicator(const char &value)
     : value{ value } {}

    // get value of SideIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
