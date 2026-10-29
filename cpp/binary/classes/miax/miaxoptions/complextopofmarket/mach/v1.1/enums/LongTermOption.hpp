#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Long Term Option
enum class LongTermOption : char {
    Yes = 'Y', // Yes
    No = 'N',  // No
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LongTermOption value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LongTermOption value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
