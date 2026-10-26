#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Event Reason value
enum class EventReason : char {
    Automatic = 'A', // Automatic
    Manual = 'M',    // Manual
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EventReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EventReason value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
