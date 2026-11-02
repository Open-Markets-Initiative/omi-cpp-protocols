#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v3 {

// The side taken for the leg when purchasing the spread
enum class LegSide : char {
    Ask = 'A',  // Ask
    Bid = 'B',  // Bid
    None = 'N', // None
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LegSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LegSide value);

} // namespace databento::marketdata::normalized::dbn::v3
