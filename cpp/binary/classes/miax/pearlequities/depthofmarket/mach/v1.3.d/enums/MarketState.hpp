#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Current market state.
enum class MarketState : std::uint8_t {
    PreOpening = 1,            // Pre Opening
    EarlyTradingSession = 2,   // Early Trading Session
    RegularTradingSession = 3, // Regular Trading Session
    LateTradingSession = 4,    // Late Trading Session
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketState value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
