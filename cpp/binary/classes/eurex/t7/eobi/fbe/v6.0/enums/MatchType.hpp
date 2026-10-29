#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v6_0 {

enum class MatchType : std::uint8_t {
    ConfirmedTradeReport = 3, // Confirmed Trade Report
    CrossAuction = 5,         // Cross Auction
    CallAuction = 7,          // Call Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MatchType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MatchType value);

} // namespace eurex::t7::eobi::fbe::v6_0
