#pragma once

#include <cstddef>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {


// A, H, Q, S, T
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
