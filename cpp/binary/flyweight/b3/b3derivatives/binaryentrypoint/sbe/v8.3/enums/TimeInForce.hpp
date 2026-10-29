#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// timeInForce
enum class TimeInForce : char {
    Day = '0',               // Day
    GoodTillCancel = '1',    // Good Till Cancel
    ImmediateOrCancel = '3', // Immediate Or Cancel
    FillOrKill = '4',        // Fill Or Kill
    GoodTillDate = '6',      // Good Till Date
    AtTheClose = '7',        // At The Close
    GoodForAuction = 'A',    // Good For Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TimeInForce value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TimeInForce value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
