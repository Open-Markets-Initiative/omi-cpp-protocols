#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Reason for the crossing from the opening and re-opening auction.
enum class CrossType : char {
    MarketCenterEarlyOpeningAuction = 'E', // Market Center Early Opening Auction
    MarketCenterOpeningAuction = 'O',      // Market Center Opening Auction
    MarketCenterReopeningAuction = '5',    // Market Center Reopening Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossType value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
