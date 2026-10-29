#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Retail price improvement value
enum class RetailPriceImprovement : char {
    BuySide = 'B',    // Buy Side
    SellSide = 'S',   // Sell Side
    BuyAndSell = 'A', // Buy And Sell
    NoRpi = 'N',      // No Rpi
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RetailPriceImprovement value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RetailPriceImprovement value);

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
