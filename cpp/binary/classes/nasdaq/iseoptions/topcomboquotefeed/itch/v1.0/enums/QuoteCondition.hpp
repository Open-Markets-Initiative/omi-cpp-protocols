#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// <space> = regular quote/autox eligible “X” = Pre-Open/Halted
enum class QuoteCondition : char {
    RegularQuote = ' ', // Regular Quote
    Halted = 'X',       // Halted
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(QuoteCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, QuoteCondition value);

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
