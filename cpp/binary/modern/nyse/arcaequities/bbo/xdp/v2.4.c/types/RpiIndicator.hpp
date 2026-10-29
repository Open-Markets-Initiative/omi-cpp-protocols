#pragma once

#include <cstddef>

namespace nyse::arcaequities::bbo::xdp::v2_4_c {


// The side(s) where Retail Price Indication orders (RPI orders) exist.
struct RpiIndicator {

    static constexpr auto name = "Rpi Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr RpiIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RpiIndicator(const char &value)
     : value{ value } {}

    // get value of RpiIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
