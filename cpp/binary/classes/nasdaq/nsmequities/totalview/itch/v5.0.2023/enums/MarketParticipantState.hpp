#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates the market participant's current registration status in the issue
enum class MarketParticipantState : char {
    Active = 'A',    // Active
    Excused = 'E',   // Excused
    Withdrawn = 'W', // Withdrawn
    Suspended = 'S', // Suspended
    Deleted = 'D',   // Deleted
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketParticipantState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketParticipantState value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
