#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Refer to System Event Codes below
enum class EventCode : char {
    StartOfMessages = 'O',                  // Start Of Messages
    StartOfSystemHours = 'S',               // Start Of System Hours
    StartOfOpeningProcess = 'Q',            // Start Of Opening Process
    StartOfNormalHoursClosingProcess = 'N', // Start Of Normal Hours Closing Process
    StartOfLateHoursClosingProcess = 'L',   // Start Of Late Hours Closing Process
    EndOfSystemHours = 'E',                 // End Of System Hours
    EndOfMessages = 'C',                    // End Of Messages
    EndOfWcoEarlyClosing = 'W',             // End Of Wco Early Closing
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EventCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EventCode value);

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
