#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Market Data entry type
enum class MdEntryTypeStatistics : char {
    OpenPrice = '4',   // Open Price
    HighTrade = '7',   // High Trade
    LowTrade = '8',    // Low Trade
    Vwap = '9',        // Vwap
    HighestBid = 'N',  // Highest Bid
    LowestOffer = 'O', // Lowest Offer
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdEntryTypeStatistics value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdEntryTypeStatistics value);

} // namespace cme::globex::mdp3::sbe::v1_13
