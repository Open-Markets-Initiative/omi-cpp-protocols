#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// Message identifier
enum class MessageCategory : char {
    Administrative = 'C',                // Administrative
    Control = 'H',                       // Control
    EquityAndIndexLastSale = 'a',        // Equity And Index Last Sale
    OpenInterest = 'd',                  // Open Interest
    EquityAndIndexEndOfDaySummary = 'f', // Equity And Index End Of Day Summary
    LongEquityAndIndexQuote = 'k',       // Long Equity And Index Quote
    ShortEquityAndIndexQuote = 'q',      // Short Equity And Index Quote
    UnderlyingValue = 'Y',               // Underlying Value
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageCategory value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageCategory value);

} // namespace siac::opra::output::obi::v6_2
