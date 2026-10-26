#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Indicates the Auction Status.
enum class AuctionStatus : std::uint8_t {
    WillRunAsUsual = 0,                                        // Will Run As Usual
    AuctionWillNotRunBecauseLegalWidthQuoteDoesNotExist = 4,   // Auction Will Not Run Because Legal Width Quote Does Not Exist
    AuctionWillNotRunBecauseMarketMakerQuoteIsNotReceived = 5, // Auction Will Not Run Because Market Maker Quote Is Not Received
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionStatus value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
