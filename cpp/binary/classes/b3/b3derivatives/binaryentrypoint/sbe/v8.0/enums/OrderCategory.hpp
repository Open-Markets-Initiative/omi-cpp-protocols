#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// orderCategory
enum class OrderCategory : char {
    ResultOfOptionsExercise = 'B',                 // Result Of Options Exercise
    ResultOfAssignmentFromAnOptionsExercise = 'C', // Result Of Assignment From An Options Exercise
    ResultOfAutomaticOptionsExercise = 'D',        // Result Of Automatic Options Exercise
    ResultOfMidpointOrder = 'E',                   // Result Of Midpoint Order
    ResultOfBlockBookTrade = 'F',                  // Result Of Block Book Trade
    ResultOfTradeAtClose = 'G',                    // Result Of Trade At Close
    ResultOfTradeAtAverage = 'H',                  // Result Of Trade At Average
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrderCategory value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrderCategory value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
