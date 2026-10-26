#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Y - Yes, N - No.
enum class TestSecurityIndicator : char {
    Yes = 'Y', // Yes
    No = 'N',  // No
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TestSecurityIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TestSecurityIndicator value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
