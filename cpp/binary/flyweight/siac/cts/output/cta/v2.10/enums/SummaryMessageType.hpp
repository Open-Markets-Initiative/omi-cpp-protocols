#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

// Summary message type
enum class SummaryMessageType : char {
    ConsolidatedStartOfDaySummaryMessage = 'A',         // Consolidated Start Of Day Summary Message
    ParticipantStartOfDaySummaryMessage = 'B',          // Participant Start Of Day Summary Message
    ConsolidatedEndOfDaySummaryMessage = 'C',           // Consolidated End Of Day Summary Message
    FractionalConsolidatedEndOfDaySummaryMessage = 'T', // Fractional Consolidated End Of Day Summary Message
    ParticipantEndOfDaySummaryMessage = 'D',            // Participant End Of Day Summary Message
    FractionalParticipantEndOfDaySummaryMessage = 'P',  // Fractional Participant End Of Day Summary Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SummaryMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SummaryMessageType value);

} // namespace siac::cts::output::cta::v2_10
