#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

// Auction Type
enum class AuctionType : char {
    OpeningAuction = 'O',    // Opening Auction
    ClosingAuction = 'C',    // Closing Auction
    HaltAuction = 'H',       // Halt Auction
    IpoAuction = 'I',        // Ipo Auction
    CboeMarketClose = 'M',   // Cboe Market Close
    VolatilityAuction = 'V', // Volatility Auction
    PeriodicAuction = 'P',   // Periodic Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
