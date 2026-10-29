#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

// Retail Price Improvement
enum class RetailPriceImprovement : char {
    BuySideRpi = 'B',    // Buy Side Rpi
    SellSideRpi = 'S',   // Sell Side Rpi
    BuyAndSellRpi = 'A', // Buy And Sell Rpi
    NoRpi = 'N',         // No Rpi
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RetailPriceImprovement value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RetailPriceImprovement value);

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
