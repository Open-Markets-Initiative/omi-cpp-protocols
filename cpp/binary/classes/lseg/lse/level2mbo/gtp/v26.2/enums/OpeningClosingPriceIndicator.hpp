#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Populated if the Statistic Type is 2 or 3.
enum class OpeningClosingPriceIndicator : char {
    Ut = 'A',            // Ut
    At = 'B',            // At
    MidOfBbo = 'C',      // Mid Of Bbo
    LastAt = 'D',        // Last At
    LastUt = 'E',        // Last Ut
    Manual = 'F',        // Manual
    PreviousClose = 'I', // Previous Close
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OpeningClosingPriceIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OpeningClosingPriceIndicator value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
