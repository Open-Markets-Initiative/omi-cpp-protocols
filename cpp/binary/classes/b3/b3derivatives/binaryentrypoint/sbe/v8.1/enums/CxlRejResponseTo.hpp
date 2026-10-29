#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// cxlRejResponseTo
enum class CxlRejResponseTo : std::uint8_t {
    New = 0,     // New
    Cancel = 1,  // Cancel
    Replace = 2, // Replace
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CxlRejResponseTo value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CxlRejResponseTo value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
