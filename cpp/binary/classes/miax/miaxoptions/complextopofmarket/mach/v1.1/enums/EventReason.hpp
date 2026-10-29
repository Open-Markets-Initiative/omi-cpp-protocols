#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Values: “A” = This event resulted from automatic/market driven event “M” = MIAX manually
// initiated this event
enum class EventReason : char {
    Automatic = 'A', // Automatic
    Manual = 'M',    // Manual
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EventReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EventReason value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
