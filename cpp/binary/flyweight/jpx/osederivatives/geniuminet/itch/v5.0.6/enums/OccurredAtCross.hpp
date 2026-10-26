#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Y=Yes, N=No
enum class OccurredAtCross : char {
    No = 'N',  // No
    Yes = 'Y', // Yes
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OccurredAtCross value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OccurredAtCross value);

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
