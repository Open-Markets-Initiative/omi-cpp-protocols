#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Market Data entry type
enum class MdEntryTypeBook : char {
    Bid = '0',             // Bid
    Offer = '1',           // Offer
    ImpliedBid = 'E',      // Implied Bid
    ImpliedOffer = 'F',    // Implied Offer
    BookReset = 'J',       // Book Reset
    MarketBestOffer = 'w', // Market Best Offer
    MarketBestBid = 'x',   // Market Best Bid
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdEntryTypeBook value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdEntryTypeBook value);

} // namespace cme::globex::mdp3::sbe::v1_13
