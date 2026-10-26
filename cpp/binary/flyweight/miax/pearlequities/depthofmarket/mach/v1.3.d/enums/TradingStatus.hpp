#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Current trading status of the security.
enum class TradingStatus : std::uint8_t {
    PreOpen = 1,         // Pre Open
    Trading = 2,         // Trading
    Halt = 3,            // Halt
    OperationalHalt = 4, // Operational Halt
    Closed = 5,          // Closed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingStatus value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
