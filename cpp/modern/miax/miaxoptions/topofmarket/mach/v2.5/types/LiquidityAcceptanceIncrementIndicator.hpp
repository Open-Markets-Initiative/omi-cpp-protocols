#pragma once

#include <cstddef>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// This is the Minimum Price Variation for Quote/Order acceptance as per MIAX rules
struct LiquidityAcceptanceIncrementIndicator {

    static constexpr auto name = "Liquidity Acceptance Increment Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LiquidityAcceptanceIncrementIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LiquidityAcceptanceIncrementIndicator(const char &value)
     : value{ value } {}

    // get value of LiquidityAcceptanceIncrementIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
