#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class TradeCondition : std::uint16_t {
    ImpliedTrade = 1,            // Implied Trade
    OutOfSequence = 107,         // Out Of Sequence
    MidpointPrice = 155,         // Midpoint Price
    TradingOnTermsOfIssue = 156, // Trading On Terms Of Issue
    SpecialAuction = 596,        // Special Auction
    TradeAtClose = 624,          // Trade At Close
    Retail = 743,                // Retail
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCondition value);

} // namespace eurex::t7::eobi::fbe::v13_0
