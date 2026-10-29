#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

// Quote condition values. For markets other than NYSE, only condition R is applicable.
enum class QuoteCondition : char {
    Closing = 'C',            // Closing
    OpeningQuote = 'O',       // Opening Quote
    RegularQuote = 'R',       // Regular Quote
    SlowOnTheBidAndAsk = 'W', // Slow On The Bid And Ask
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(QuoteCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, QuoteCondition value);

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
