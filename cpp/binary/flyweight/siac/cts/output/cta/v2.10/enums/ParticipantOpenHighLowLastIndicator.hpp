#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

// Identifies the Participant Open/High/Low/Last applicable to the transaction
enum class ParticipantOpenHighLowLastIndicator : char {
    None = 'A',            // None
    High = 'B',            // High
    Low = 'C',             // Low
    Last = 'D',            // Last
    HighLast = 'E',        // High Last
    LowLast = 'F',         // Low Last
    Unused = 'G',          // Unused
    Open = 'H',            // Open
    OpenHigh = 'I',        // Open High
    OpenLow = 'J',         // Open Low
    OpenHighLowLast = 'K', // Open High Low Last
    OpenLast = 'L',        // Open Last
    OpenHighLow = 'M',     // Open High Low
    OpenHighLast = 'N',    // Open High Last
    OpenLowLast = 'O',     // Open Low Last
    HighLow = 'P',         // High Low
    HighLowLast = 'Q',     // High Low Last
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ParticipantOpenHighLowLastIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ParticipantOpenHighLowLastIndicator value);

} // namespace siac::cts::output::cta::v2_10
