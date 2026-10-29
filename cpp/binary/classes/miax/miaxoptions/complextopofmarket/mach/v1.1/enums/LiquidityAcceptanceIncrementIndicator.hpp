#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// This is the Minimum Price Variation for Quote/Order acceptance as per MIAX rules
enum class LiquidityAcceptanceIncrementIndicator : char {
    Penny = 'P',  // Penny
    Nickel = 'N', // Nickel
    Dime = 'D',   // Dime
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LiquidityAcceptanceIncrementIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LiquidityAcceptanceIncrementIndicator value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
