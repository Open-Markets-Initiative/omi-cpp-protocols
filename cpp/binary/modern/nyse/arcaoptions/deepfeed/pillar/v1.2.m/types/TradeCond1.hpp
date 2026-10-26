#pragma once

#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Settlement related conditions.
struct TradeCond1 {

    static constexpr auto name = "Trade Cond 1";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradeCond1()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeCond1(const char &value)
     : value{ value } {}

    // get value of TradeCond1 field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
