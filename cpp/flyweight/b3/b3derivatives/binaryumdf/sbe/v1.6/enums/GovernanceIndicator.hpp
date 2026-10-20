#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// governanceIndicator
enum class GovernanceIndicator : std::uint8_t {
    No = 0, // No
    N1 = 1, // N 1
    N2 = 2, // N 2
    Nm = 4, // Nm
    Ma = 5, // Ma
    Mb = 6, // Mb
    M2 = 7, // M 2
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(GovernanceIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, GovernanceIndicator value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
