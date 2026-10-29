#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// See System Event Codes.
enum class EventCode : char {
    StartOfMessages = 'O',                         // Start Of Messages
    StartOfSystemHours = 'S',                      // Start Of System Hours
    StartOfMarketHours = 'Q',                      // Start Of Market Hours
    EndOfMarketHours = 'M',                        // End Of Market Hours
    EndOfSystemHours = 'E',                        // End Of System Hours
    EndOfMessages = 'C',                           // End Of Messages
    EmergencyMarketConditionHalt = 'A',            // Emergency Market Condition Halt
    EmergencyMarketConditionQuoteOnlyPeriod = 'R', // Emergency Market Condition Quote Only Period
    EmergencyMarketConditionResumption = 'B',      // Emergency Market Condition Resumption
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EventCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EventCode value);

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
