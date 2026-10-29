#pragma once

#include <cstddef>

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {


// The reason for Trade Through Exemptions.
struct TradeCond2 {

    static constexpr auto name = "Trade Cond 2";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradeCond2()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeCond2(const char &value)
     : value{ value } {}

    // get value of TradeCond2 field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
