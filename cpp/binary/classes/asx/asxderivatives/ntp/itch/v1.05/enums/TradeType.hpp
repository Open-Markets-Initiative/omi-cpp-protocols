#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Nature of the match
enum class TradeType : char {
    NormalTrade = 'T',                   // Normal Trade
    NormalCross = 't',                   // Normal Cross
    AuctionTrade = 'L',                  // Auction Trade
    AuctionCross = 'l',                  // Auction Cross
    CombinationToUnderlyingTrade = 'S',  // Combination To Underlying Trade
    CombinationToUnderlyingCross = 's',  // Combination To Underlying Cross
    CombinationToCombinationTrade = 'R', // Combination To Combination Trade
    CombinationToCombinationCross = 'r', // Combination To Combination Cross
    StripToStripTrade = 'A',             // Strip To Strip Trade
    StripToStripCross = 'a',             // Strip To Strip Cross
    StripToOutrightTrade = 'B',          // Strip To Outright Trade
    StripToOutrightCross = 'b',          // Strip To Outright Cross
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeType value);

} // namespace asx::asxderivatives::ntp::itch::v1_05
