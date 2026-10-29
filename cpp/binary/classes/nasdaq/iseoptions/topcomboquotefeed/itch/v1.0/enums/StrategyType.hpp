#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// StrategyType value
enum class StrategyType : char {
    VerticalSpread = 'V', // Vertical Spread
    TimeSpread = 'T',     // Time Spread
    DiagonalSpread = 'D', // Diagonal Spread
    Straddle = 'S',       // Straddle
    Strangle = 'G',       // Strangle
    Combo = 'C',          // Combo
    RiskReversal = 'R',   // Risk Reversal
    RatioSpread = 'A',    // Ratio Spread
    Custom = 'U',         // Custom
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(StrategyType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, StrategyType value);

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
