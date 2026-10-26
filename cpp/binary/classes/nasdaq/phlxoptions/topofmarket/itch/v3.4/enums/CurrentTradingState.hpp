#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Reflects the current trading state for the option in the options market.
enum class CurrentTradingState : char {
    HaltInEffect = 'H',   // Halt In Effect
    TradingResumed = 'T', // Trading Resumed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CurrentTradingState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CurrentTradingState value);

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
