#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v2_10_a {

// Identifies the type of Quote message
enum class QuoteMessageType : char {
    AuctionStatus = 'A',    // Auction Status
    LongQuote = 'L',        // Long Quote
    ShortQuote = 'Q',       // Short Quote
    SpecialLongQuote = 'S', // Special Long Quote
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(QuoteMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, QuoteMessageType value);

} // namespace siac::cqs::output::cta::v2_10_a
