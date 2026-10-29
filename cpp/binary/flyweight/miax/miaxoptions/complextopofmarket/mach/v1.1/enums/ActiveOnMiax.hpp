#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Indicates if this symbol is tradable on MIAX in the current session: “A” = Active (tradable)
// on MIAX “I” = Inactive (not tradable) on MIAX
enum class ActiveOnMiax : char {
    Active = 'A',   // Active
    Inactive = 'I', // Inactive
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ActiveOnMiax value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ActiveOnMiax value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
