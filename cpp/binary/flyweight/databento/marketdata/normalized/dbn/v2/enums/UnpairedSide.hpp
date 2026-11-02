#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v2 {

// Reserved for future use
enum class UnpairedSide : char {
    Ask = 'A',  // Ask
    Bid = 'B',  // Bid
    None = 'N', // None
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(UnpairedSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, UnpairedSide value);

} // namespace databento::marketdata::normalized::dbn::v2
