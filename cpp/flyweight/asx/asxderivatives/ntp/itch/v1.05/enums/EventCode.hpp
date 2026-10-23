#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Event Code
enum class EventCode : char {
    BusinessTradeDateHasEnded = 'C', // Business Trade Date Has Ended
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EventCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EventCode value);

} // namespace asx::asxderivatives::ntp::itch::v1_05
