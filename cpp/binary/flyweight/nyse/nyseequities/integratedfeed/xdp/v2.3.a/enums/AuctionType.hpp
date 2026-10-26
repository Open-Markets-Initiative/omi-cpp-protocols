#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// Type of auction
enum class AuctionType : char {
    EarlyOpeningAuctionNonNyseOnly = 'O', // Early Opening Auction Non Nyse Only
    CoreOpeningAuction = 'M',             // Core Opening Auction
    ReopeningAuctionHaltResume = 'H',     // Reopening Auction Halt Resume
    ClosingAuction = 'C',                 // Closing Auction
    ExtremeClosingImbalance = 'P',        // Extreme Closing Imbalance
    RegulatoryClosingImbalance = 'R',     // Regulatory Closing Imbalance
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
