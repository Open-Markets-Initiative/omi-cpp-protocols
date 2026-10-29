#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Trading Status
enum class TradingStatus : std::uint8_t {
    PreOpen = 1,         // Pre Open
    OpeningFreeze = 2,   // Opening Freeze
    Trading = 3,         // Trading
    Halt = 4,            // Halt
    OperationalHalt = 5, // Operational Halt
    Closed = 6,          // Closed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingStatus value);

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
