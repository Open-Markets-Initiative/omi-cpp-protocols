#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

// Reason for the crossing auction.
enum class CrossType : char {
    MarketCenterEarlyOpeningAuction = 'E', // Market Center Early Opening Auction
    MarketCenterOpeningAuction = 'O',      // Market Center Opening Auction
    MarketCenterReopeningAuction = '5',    // Market Center Reopening Auction
    MarketCenterClosingAuction = '6',      // Market Center Closing Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossType value);

} // namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g
