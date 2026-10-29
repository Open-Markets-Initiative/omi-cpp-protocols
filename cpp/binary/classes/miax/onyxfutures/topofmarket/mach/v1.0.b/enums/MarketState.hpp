#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Market State
enum class MarketState : std::uint8_t {
    PreOpening = 1,              // Pre Opening
    Extended1TradingSession = 2, // Extended 1 Trading Session
    RegularTradingSession = 3,   // Regular Trading Session
    Extended2TradingSession = 4, // Extended 2 Trading Session
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketState value);

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
