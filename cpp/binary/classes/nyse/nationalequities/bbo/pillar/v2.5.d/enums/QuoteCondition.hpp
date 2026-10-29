#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nationalequities::bbo::pillar::v2_5_d {

// Quote Condition
enum class QuoteCondition : char {
    RegularQuote = 'R', // Regular Quote
    OpeningQuote = 'O', // Opening Quote
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(QuoteCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, QuoteCondition value);

} // namespace nyse::nationalequities::bbo::pillar::v2_5_d
