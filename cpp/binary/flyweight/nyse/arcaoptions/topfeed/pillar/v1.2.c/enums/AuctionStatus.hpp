#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Indicates whether the auction will run
enum class AuctionStatus : std::uint8_t {
    Usual = 0,                         // Usual
    LegalWidthQuoteDoesNotExist = 4,   // Legal Width Quote Does Not Exist
    MarketMakerQuoteIsNotReceived = 5, // Market Maker Quote Is Not Received
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionStatus value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
