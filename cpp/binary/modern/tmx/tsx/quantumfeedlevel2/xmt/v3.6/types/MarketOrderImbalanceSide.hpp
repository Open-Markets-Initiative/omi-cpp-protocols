// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/MarketOrderImbalanceSide.hpp
#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// Side Buy Or Sell Of The Market Order Imbalance Volume
struct MarketOrderImbalanceSide {

    static constexpr auto name = "Market Order Imbalance Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MarketOrderImbalanceSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketOrderImbalanceSide(const char &value)
     : value{ value } {}

    // get value of MarketOrderImbalanceSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
