#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v1_91 {

// Represents for a Participant the upward, downward or unchanged price movement in a
// security's trades
enum class Tick : char {
    NotApplicable = ' ',     // Not Applicable
    Upward = '1',            // Upward
    Downward = '2',          // Downward
    UnchangedUpward = '3',   // Unchanged Upward
    UnchangedDownward = '4', // Unchanged Downward
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Tick value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Tick value);

} // namespace siac::cts::output::cta::v1_91
