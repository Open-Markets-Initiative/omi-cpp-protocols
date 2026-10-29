#pragma once

#include <cstddef>

namespace nyse::nationalequities::bbo::pillar::v2_5_d {


// The side(s) where Retail Price Indication orders (RPI orders) exist. Values correspond to CQS values.
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
