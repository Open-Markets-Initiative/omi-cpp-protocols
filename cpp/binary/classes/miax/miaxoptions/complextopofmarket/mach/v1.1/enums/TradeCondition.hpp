#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Trade Condition Type
enum class TradeCondition : char {
    Matched = 'S', // Matched
    Legged = 'L',  // Legged
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCondition value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
