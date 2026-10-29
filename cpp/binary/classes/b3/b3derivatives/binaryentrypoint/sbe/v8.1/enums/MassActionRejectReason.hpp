#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// massActionRejectReason
enum class MassActionRejectReason : std::uint8_t {
    MassActionNotSupported = 0,        // Mass Action Not Supported
    InvalidOrUnknownMarketSegment = 8, // Invalid Or Unknown Market Segment
    Other = 99,                        // Other
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MassActionRejectReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MassActionRejectReason value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
