#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// ordStatus
enum class OrdStatus : char {
    New = '0',                // New
    PartiallyFilled = '1',    // Partially Filled
    Filled = '2',             // Filled
    Canceled = '4',           // Canceled
    Replaced = '5',           // Replaced
    Rejected = '8',           // Rejected
    Expired = 'C',            // Expired
    Restated = 'R',           // Restated
    PreviousFinalState = 'Z', // Previous Final State
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrdStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrdStatus value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
