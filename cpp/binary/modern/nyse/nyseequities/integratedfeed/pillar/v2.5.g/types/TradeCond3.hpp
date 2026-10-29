#pragma once

#include <cstddef>

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {


// Extended hours/sequencing related conditions.
struct TradeCond3 {

    static constexpr auto name = "Trade Cond 3";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradeCond3()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeCond3(const char &value)
     : value{ value } {}

    // get value of TradeCond3 field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
