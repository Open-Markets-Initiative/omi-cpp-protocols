#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Refer to System Event Codes below
enum class EventCode : char {
    StartOfMessages = 'O',            // Start Of Messages
    StartOfSystemHours = 'S',         // Start Of System Hours
    StartOfOpeningProcess = 'Q',      // Start Of Opening Process
    EndOfNormalHoursProcessing = 'N', // End Of Normal Hours Processing
    EndOfLateHoursProcessing = 'L',   // End Of Late Hours Processing
    EndOfSystemHours = 'E',           // End Of System Hours
    EndOfMessages = 'C',              // End Of Messages
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EventCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EventCode value);

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
