#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

// Denotes the operational halt action
enum class OperationalHaltAction : char {
    Halted = 'H',  // Halted
    Resumed = 'T', // Resumed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OperationalHaltAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OperationalHaltAction value);

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
