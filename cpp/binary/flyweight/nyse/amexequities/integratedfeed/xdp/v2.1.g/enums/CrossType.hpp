#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// Reason for the crossing auction.
enum class CrossType : char {
    EarlyOpening = 'E', // Early Opening
    Opening = 'O',      // Opening
    Reopening = '5',    // Reopening
    Closing = '6',      // Closing
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossType value);

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
