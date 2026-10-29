#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Denotes whether the issue is operationally halted on the identified market or has resumed
// trading
enum class OperationalHaltAction : char {
    Halted = 'H',  // Halted
    Trading = 'T', // Trading
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OperationalHaltAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OperationalHaltAction value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
