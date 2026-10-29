#pragma once

#include <cstddef>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {


// The side of the order. Valid values: ‘B’ – Buy ‘S’ – Sell
struct Side {

    static constexpr auto name = "Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Side()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Side(const char &value)
     : value{ value } {}

    // get value of Side field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
