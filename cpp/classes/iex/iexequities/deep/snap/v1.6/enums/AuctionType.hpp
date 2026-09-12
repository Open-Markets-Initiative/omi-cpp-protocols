#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::deep::snap::v1_6 {

// Auction type identifier
enum class AuctionType : char {
    OpeningAuction = 'O',    // Opening Auction
    ClosingAuction = 'C',    // Closing Auction
    IpoAuction = 'I',        // Ipo Auction
    HaltAuction = 'H',       // Halt Auction
    VolatilityAuction = 'V', // Volatility Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace iex::iexequities::deep::snap::v1_6
