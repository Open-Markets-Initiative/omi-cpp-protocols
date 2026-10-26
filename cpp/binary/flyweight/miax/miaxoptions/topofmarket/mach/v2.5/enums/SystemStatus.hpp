#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Current system status
enum class SystemStatus : char {
    StartOfSystemHours = 'S', // Start Of System Hours
    EndOfSystemHours = 'C',   // End Of System Hours
    StartOfTestSession = '1', // Start Of Test Session
    EndOfTestSession = '2',   // End Of Test Session
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SystemStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SystemStatus value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
