#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// Used to identify the type of quantity.
enum class PosType : char {
    TransactionQuantity = 'T', // Transaction Quantity
    StartOfDayQty = 'S',       // Start Of Day Qty
    OptionExerciseQty = 'E',   // Option Exercise Qty
    BlockedQty = 'B',          // Blocked Qty
    UncoveredQty = 'U',        // Uncovered Qty
    CoveredQty = 'C',          // Covered Qty
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PosType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PosType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
