#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// timeInForce
enum class TimeInForceSimple : char {
    Day = '0',               // Day
    ImmediateOrCancel = '3', // Immediate Or Cancel
    FillOrKill = '4',        // Fill Or Kill
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TimeInForceSimple value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TimeInForceSimple value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
