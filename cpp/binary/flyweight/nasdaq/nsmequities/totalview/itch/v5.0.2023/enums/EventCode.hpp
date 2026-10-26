#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// System Event Codes
enum class EventCode : char {
    StartOfMessages = 'O',    // Start Of Messages
    StartOfSystemHours = 'S', // Start Of System Hours
    StartOfMarketHours = 'Q', // Start Of Market Hours
    EndOfMarketHours = 'M',   // End Of Market Hours
    EndOfSystemHours = 'E',   // End Of System Hours
    EndOfMessages = 'C',      // End Of Messages
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EventCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EventCode value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
