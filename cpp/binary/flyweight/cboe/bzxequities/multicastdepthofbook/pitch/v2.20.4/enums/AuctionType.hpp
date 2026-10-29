#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// "O" = Opening Auction "C" = Closing Auction "H" = Halt Auction "I" = IPO Auction
enum class AuctionType : char {
    OpeningAuction = 'O', // Opening Auction
    ClosingAuction = 'C', // Closing Auction
    HaltAuction = 'H',    // Halt Auction
    IpoAuction = 'I',     // Ipo Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
