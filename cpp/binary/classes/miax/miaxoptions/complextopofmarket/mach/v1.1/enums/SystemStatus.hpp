#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Current system status: “S” = Start of System hours “C” = End of System hours, “1” = Start of
// Test Session (sent before tests). “2” = End of Test Session.
enum class SystemStatus : char {
    StartOfSystemHours = 'S', // Start Of System Hours
    EndOfSystemHours = 'C',   // End Of System Hours
    StartTestSession = '1',   // Start Test Session
    EndOfTestSession = '2',   // End Of Test Session
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SystemStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SystemStatus value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
