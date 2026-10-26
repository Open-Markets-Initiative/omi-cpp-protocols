#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the type of Summary message
enum class SummaryMessageType : char {
    ConsolidatedStartOfDaySummary = 'A',         // Consolidated Start Of Day Summary
    ParticipantStartOfDaySummary = 'B',          // Participant Start Of Day Summary
    ConsolidatedEndOfDaySummary = 'C',           // Consolidated End Of Day Summary
    FractionalConsolidatedEndOfDaySummary = 'T', // Fractional Consolidated End Of Day Summary
    ParticipantEndOfDaySummary = 'D',            // Participant End Of Day Summary
    FractionalParticipantEndOfDaySummary = 'P',  // Fractional Participant End Of Day Summary
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SummaryMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SummaryMessageType value);

} // namespace siac::cts::output::cta::v2_11_b
