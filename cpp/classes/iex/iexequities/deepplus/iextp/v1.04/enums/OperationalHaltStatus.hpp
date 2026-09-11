#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::deepplus::iextp::v1_04 {

// Operational halt status identifier
enum class OperationalHaltStatus : char {
    IexSpecificOperationalTradingHalt = 'O', // Iex Specific Operational Trading Halt
    NotOperationallyHaltedOnIex = 'N',       // Not Operationally Halted On Iex
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OperationalHaltStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OperationalHaltStatus value);

} // namespace iex::iexequities::deepplus::iextp::v1_04
