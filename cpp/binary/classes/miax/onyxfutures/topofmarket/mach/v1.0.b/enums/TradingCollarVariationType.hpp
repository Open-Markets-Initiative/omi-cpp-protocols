#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Trading Collar Variation Type
enum class TradingCollarVariationType : char {
    ProductDollarCollarValue = 'D',     // Product Dollar Collar Value
    ProductCollarPercentageValue = 'P', // Product Collar Percentage Value
    StandardCalendarSpread = 'S',       // Standard Calendar Spread
    EquityCalendarSpread = 'E',         // Equity Calendar Spread
    ButterflySpread = 'B',              // Butterfly Spread
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingCollarVariationType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingCollarVariationType value);

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
