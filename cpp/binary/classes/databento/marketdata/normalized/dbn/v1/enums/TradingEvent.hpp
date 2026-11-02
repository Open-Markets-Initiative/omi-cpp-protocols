#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v1 {

// Further information about a status update
enum class TradingEvent : std::uint16_t {
    None = 0,                 // None
    NoCancel = 1,             // No Cancel
    ChangeTradingSession = 2, // Change Trading Session
    ImpliedMatchingOn = 3,    // Implied Matching On
    ImpliedMatchingOff = 4,   // Implied Matching Off
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingEvent value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingEvent value);

} // namespace databento::marketdata::normalized::dbn::v1
