#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::tops::snap::v1_6 {

// Retail Liquidity Indicator identifier
enum class RetailLiquidityIndicator : char {
    NotApplicable = ' ',      // Not Applicable
    BuyInterest = 'A',        // Buy Interest
    SellInterest = 'B',       // Sell Interest
    BuyAndSellInterest = 'C', // Buy And Sell Interest
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RetailLiquidityIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RetailLiquidityIndicator value);

} // namespace iex::iexequities::tops::snap::v1_6
