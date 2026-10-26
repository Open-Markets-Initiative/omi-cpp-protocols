#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Identifies side of the RFQ
enum class RfqSide : char {
    TwoSidedQuote = 'T', // Two Sided Quote
    BidQuote = 'B',      // Bid Quote
    AskQuote = 'S',      // Ask Quote
    Crossing = 'X',      // Crossing
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RfqSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RfqSide value);

} // namespace asx::asxderivatives::ntp::itch::v1_05
