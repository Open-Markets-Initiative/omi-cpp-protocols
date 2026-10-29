#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::ouch::v1_11 {


// Identifies whether this would-be trade was a result of a liquidity provider providing or liquidity taker taking the liquidity
struct LiquidityIndicator {

    static constexpr auto name = "Liquidity Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LiquidityIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LiquidityIndicator(const char &value)
     : value{ value } {}

    // get value of LiquidityIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
