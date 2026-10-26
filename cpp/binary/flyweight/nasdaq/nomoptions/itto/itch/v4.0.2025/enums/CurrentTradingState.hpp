#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Reflects the current trading state for the options security in the NASDAQ Options Market.
// The allowable values are:
enum class CurrentTradingState : char {
    Halt = 'H',                     // Halt
    Trading = 'T',                  // Trading
    BuySideTradingSuspended = 'B',  // Buy Side Trading Suspended
    SellSideTradingSuspended = 'S', // Sell Side Trading Suspended
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CurrentTradingState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CurrentTradingState value);

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
