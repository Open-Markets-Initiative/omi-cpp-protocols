#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Trading Status value
enum class TradingStatus : char {
    Halted = 'H',  // Halted
    Resumed = 'R', // Resumed
    Opened = 'O',  // Opened
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingStatus value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
