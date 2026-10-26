#pragma once

#include <cstddef>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {


// Populated with M if price is monetary value
struct PriceNotation {

    static constexpr auto name = "Price Notation";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr PriceNotation()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceNotation(const char &value)
     : value{ value } {}

    // get value of PriceNotation field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
