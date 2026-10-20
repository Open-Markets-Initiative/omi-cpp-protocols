#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::tops::iextp::v1_64 {

// Security event identifier
enum class SecurityEvent : char {
    OpeningProcessComplete = 'O', // Opening Process Complete
    ClosingProcessComplete = 'C', // Closing Process Complete
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityEvent value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityEvent value);

} // namespace iex::iexequities::tops::iextp::v1_64
