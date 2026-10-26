#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// This is the Minimum Price Variation for Quote/Order acceptance as per MIAX rules
enum class LiquidityAcceptanceIncrementIndicator : char {
    Penny = 'P',         // Penny
    PennyOrNickel = 'N', // Penny Or Nickel
    NickelOrDime = 'D',  // Nickel Or Dime
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LiquidityAcceptanceIncrementIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LiquidityAcceptanceIncrementIndicator value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
