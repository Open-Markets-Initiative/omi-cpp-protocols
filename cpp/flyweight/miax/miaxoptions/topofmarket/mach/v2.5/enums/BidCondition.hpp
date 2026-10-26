#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Bid Condition Values
enum class BidCondition : char {
    Regular = 'A',                // Regular
    PublicCustomerInterest = 'B', // Public Customer Interest
    NotFirm = 'C',                // Not Firm
    Reserved = 'R',               // Reserved
    TradingHalt = 'T',            // Trading Halt
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(BidCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, BidCondition value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
