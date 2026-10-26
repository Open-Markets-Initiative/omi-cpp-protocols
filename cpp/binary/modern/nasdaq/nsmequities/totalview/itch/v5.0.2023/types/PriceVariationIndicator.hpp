#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Indicates the absolute value of the percentage of deviation of the Near Indicative Clearing Price to the nearest Current Reference Price
struct PriceVariationIndicator {

    static constexpr auto name = "Price Variation Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr PriceVariationIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceVariationIndicator(const char &value)
     : value{ value } {}

    // get value of PriceVariationIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
