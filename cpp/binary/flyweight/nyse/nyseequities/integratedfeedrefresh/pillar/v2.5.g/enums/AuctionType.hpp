#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeedrefresh::pillar::v2_5_g {

// Auction type indicator.
enum class AuctionType : char {
    EarlyOpeningAuction = 'O',         // Early Opening Auction
    CoreOpeningAuction = 'M',          // Core Opening Auction
    ReopeningAuctionHaltResume = 'H',  // Reopening Auction Halt Resume
    ClosingAuction = 'C',              // Closing Auction
    ExtremeClosingImbalance = 'P',     // Extreme Closing Imbalance
    SignificantClosingImbalance = 'R', // Significant Closing Imbalance
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace nyse::nyseequities::integratedfeedrefresh::pillar::v2_5_g
