#pragma once

#include <cstddef>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {


// H = Halted, L = Curb Trading (C1 Only), Q = Quote-Only, R = Opening Rotation, T = RTH Trading.
struct TradingStatus {

    static constexpr auto name = "Trading Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradingStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingStatus(const char &value)
     : value{ value } {}

    // get value of TradingStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
