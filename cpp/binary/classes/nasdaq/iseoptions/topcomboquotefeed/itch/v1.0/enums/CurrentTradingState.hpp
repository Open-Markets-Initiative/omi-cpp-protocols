#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Reflects the current trading state for the strategy on the ISE market.
enum class CurrentTradingState : char {
    HaltInEffect = 'H',   // Halt In Effect
    TradingResumed = 'T', // Trading Resumed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CurrentTradingState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CurrentTradingState value);

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
