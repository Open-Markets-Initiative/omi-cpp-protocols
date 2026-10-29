#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// allocNoOrdersType
enum class AllocNoOrdersType : char {
    NotSpecified = '0', // Not Specified
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AllocNoOrdersType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AllocNoOrdersType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
