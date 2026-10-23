#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// G = GTH Opening (C1 Only), O = RTH Opening (C1 Only), H = Halt Re-Opening, V = Volatility
// Opening.
enum class AuctionType : char {
    OpeningAuction = 'O',    // Opening Auction
    ClosingAuction = 'C',    // Closing Auction
    GthOpening = 'G',        // Gth Opening
    HaltAuction = 'H',       // Halt Auction
    IpoAuction = 'I',        // Ipo Auction
    CboeMarketClose = 'M',   // Cboe Market Close
    VolitilityAuction = 'V', // Volitility Auction
    PeriodicAuction = 'P',   // Periodic Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
