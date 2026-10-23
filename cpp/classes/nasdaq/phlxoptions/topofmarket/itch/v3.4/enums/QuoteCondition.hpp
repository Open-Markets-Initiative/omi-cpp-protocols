#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Quote Condition value
enum class QuoteCondition : char {
    RegularQuoteautoxEligible = ' ', // Regular Quoteautox Eligible
    NonFirmQuote = 'F',              // Non Firm Quote
    RotationalQuote = 'R',           // Rotational Quote
    BidSideFirm = 'X',               // Bid Side Firm
    AskSideFirm = 'Y',               // Ask Side Firm
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(QuoteCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, QuoteCondition value);

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
