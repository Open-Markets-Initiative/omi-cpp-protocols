#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::millennium::level2::mitch::v11_9 {

enum class OpenClosePriceIndicator : char {
    Ut = 'A',                       // Ut
    At = 'B',                       // At
    MidOfBbo = 'C',                 // Mid Of Bbo
    LastAt = 'D',                   // Last At
    LastUt = 'E',                   // Last Ut
    Manual = 'F',                   // Manual
    DerivedFromPreviousClose = 'I', // Derived From Previous Close
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OpenClosePriceIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OpenClosePriceIndicator value);

} // namespace lseg::millennium::level2::mitch::v11_9
