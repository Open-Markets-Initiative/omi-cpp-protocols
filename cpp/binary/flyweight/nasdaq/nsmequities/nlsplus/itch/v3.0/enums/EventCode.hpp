#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Denotes the Nls Plus type of system event for which the message is being generated
enum class EventCode : char {
    StartOfTransmissions = 'O', // Start Of Transmissions
    StartOfSystemHours = 'S',   // Start Of System Hours
    StartOfMarketHours = 'Q',   // Start Of Market Hours
    EndOfMarketHours = 'M',     // End Of Market Hours
    EndOfSystemHours = 'E',     // End Of System Hours
    EndOfTransmissions = 'C',   // End Of Transmissions
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EventCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EventCode value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
