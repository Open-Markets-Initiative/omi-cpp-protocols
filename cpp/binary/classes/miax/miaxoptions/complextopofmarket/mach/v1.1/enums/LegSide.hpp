#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// The side of this individual leg
enum class LegSide : char {
    Bid = 'B', // Bid
    Ask = 'A', // Ask
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LegSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LegSide value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
