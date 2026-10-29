#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

// Indicates whether the auction will run.
enum class AuctionStatus : std::uint8_t {
    WillRunAsAlwaysForOpenAndClose = 0,                              // Will Run As Always For Open And Close
    WillRunInterestExistsInsideOrAtTheCollarsOrIsFullyPairedOff = 1, // Will Run Interest Exists Inside Or At The Collars Or Is Fully Paired Off
    WillNotRunBecauseThereIsAnImbalanceThroughTheCollars = 2,        // Will Not Run Because There Is An Imbalance Through The Collars
    WillNotRunWillTransitionToTheClosingAuctionInstead = 3,          // Will Not Run Will Transition To The Closing Auction Instead
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionStatus value);

} // namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g
