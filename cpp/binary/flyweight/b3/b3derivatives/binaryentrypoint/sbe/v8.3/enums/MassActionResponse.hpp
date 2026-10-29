#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// massActionResponse
enum class MassActionResponse : char {
    Rejected = '0', // Rejected
    Accepted = '1', // Accepted
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MassActionResponse value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MassActionResponse value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
