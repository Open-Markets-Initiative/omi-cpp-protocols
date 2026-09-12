#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::deep::snap::v1_6 {

// System event identifier
enum class SystemEvent : char {
    StartOfMessages = 'O',           // Start Of Messages
    StartOfSystemHours = 'S',        // Start Of System Hours
    StartOfRegularMarketHours = 'R', // Start Of Regular Market Hours
    EndOfRegularMarketHours = 'M',   // End Of Regular Market Hours
    EndOfSystemHours = 'E',          // End Of System Hours
    EndOfMessages = 'C',             // End Of Messages
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SystemEvent value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SystemEvent value);

} // namespace iex::iexequities::deep::snap::v1_6
