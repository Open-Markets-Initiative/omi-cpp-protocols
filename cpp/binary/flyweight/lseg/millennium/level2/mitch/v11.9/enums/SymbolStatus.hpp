#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::millennium::level2::mitch::v11_9 {

// This field will contain a space if the instrument is active.
enum class SymbolStatus : char {
    Active = ' ',    // Active
    Suspended = 'S', // Suspended
    Inactive = 'a',  // Inactive
    Halt = 'H',      // Halt
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SymbolStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SymbolStatus value);

} // namespace lseg::millennium::level2::mitch::v11_9
