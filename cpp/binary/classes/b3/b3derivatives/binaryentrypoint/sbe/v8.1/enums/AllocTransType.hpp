#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// allocTransType
enum class AllocTransType : char {
    New = '0',    // New
    Cancel = '2', // Cancel
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AllocTransType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AllocTransType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
