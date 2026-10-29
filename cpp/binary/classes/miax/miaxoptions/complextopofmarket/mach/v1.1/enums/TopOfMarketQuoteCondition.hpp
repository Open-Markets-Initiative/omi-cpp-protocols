#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Top of Strategy Market Quote Conditions
enum class TopOfMarketQuoteCondition : char {
    Halted = 'H',  // Halted
    Resumed = 'R', // Resumed
    Opened = 'O',  // Opened
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TopOfMarketQuoteCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TopOfMarketQuoteCondition value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
