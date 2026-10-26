#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Represents for a Participant the upward, downward or unchanged price movement in a
// security's trades
enum class Tick : char {
    TickNotApplicable = ' ', // Tick Not Applicable
    UpTick = '1',            // Up Tick
    DownTick = '2',          // Down Tick
    ZeroUpTick = '3',        // Zero Up Tick
    ZeroDownTick = '4',      // Zero Down Tick
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Tick value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Tick value);

} // namespace siac::cts::output::cta::v2_11_b
