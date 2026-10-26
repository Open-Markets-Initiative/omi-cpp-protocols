#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Identifies an additional event or a rule related to the status
enum class SecurityTradingEvent : std::uint8_t {
    NoEvent = 0,            // No Event
    NoCancel = 1,           // No Cancel
    ResetStatistics = 4,    // Reset Statistics
    ImpliedMatchingOn = 5,  // Implied Matching On
    ImpliedMatchingOff = 6, // Implied Matching Off
    EndOfWorkup = 7,        // End Of Workup
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityTradingEvent value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityTradingEvent value);

} // namespace cme::globex::mdp3::sbe::v1_13
