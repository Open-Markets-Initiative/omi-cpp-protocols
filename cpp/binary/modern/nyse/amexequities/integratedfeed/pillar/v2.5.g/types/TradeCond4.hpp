#pragma once

#include <cstddef>

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {


// SRO Required Detail.
struct TradeCond4 {

    static constexpr auto name = "Trade Cond 4";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradeCond4()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeCond4(const char &value)
     : value{ value } {}

    // get value of TradeCond4 field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
