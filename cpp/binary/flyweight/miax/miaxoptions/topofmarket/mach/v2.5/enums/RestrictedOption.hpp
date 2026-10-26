#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Restricted Option value
enum class RestrictedOption : char {
    AcceptPositionClosing = 'Y', // Accept Position Closing
    AcceptOpenAndClose = 'N',    // Accept Open And Close
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RestrictedOption value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RestrictedOption value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
