#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Closing Only Indicator
enum class ClosingOnlyIndicator : char {
    StandardSeries = '0', // Standard Series
    Call = '1',           // Call
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ClosingOnlyIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ClosingOnlyIndicator value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
