#pragma once

#include <cstddef>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// The type of order being added.
struct MarketSide {

    static constexpr auto name = "Market Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MarketSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketSide(const char &value)
     : value{ value } {}

    // get value of MarketSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
