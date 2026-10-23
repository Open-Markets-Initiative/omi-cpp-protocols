#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Trade Condition Values
enum class TradeCondition : char {
    NormalTrade = ' ',            // Normal Trade
    OpeningTrade = 'O',           // Opening Trade
    SpreadTrade = 'S',            // Spread Trade
    BlockTrade = 'B',             // Block Trade
    EcrpTrade = 'E',              // Ecrp Trade
    Derived = 'D',                // Derived
    InterMarketSpreadTrade = 'I', // Inter Market Spread Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCondition value);

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
