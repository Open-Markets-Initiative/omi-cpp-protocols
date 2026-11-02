#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v3 {

// The type of statistic value contained in the message
enum class StatType : std::uint16_t {
    OpeningPrice = 1,                 // Opening Price
    IndicativeOpeningPrice = 2,       // Indicative Opening Price
    SettlementPrice = 3,              // Settlement Price
    TradingSessionLowPrice = 4,       // Trading Session Low Price
    TradingSessionHighPrice = 5,      // Trading Session High Price
    ClearedVolume = 6,                // Cleared Volume
    LowestOffer = 7,                  // Lowest Offer
    HighestBid = 8,                   // Highest Bid
    OpenInterest = 9,                 // Open Interest
    FixingPrice = 10,                 // Fixing Price
    ClosePrice = 11,                  // Close Price
    NetChange = 12,                   // Net Change
    Vwap = 13,                        // Vwap
    Volatility = 14,                  // Volatility
    Delta = 15,                       // Delta
    UncrossingPrice = 16,             // Uncrossing Price
    UpperPriceLimit = 17,             // Upper Price Limit
    LowerPriceLimit = 18,             // Lower Price Limit
    BlockVolume = 19,                 // Block Volume
    IndicativeClosePrice = 20,        // Indicative Close Price
    MwcbLevel1 = 21,                  // Mwcb Level1
    MwcbLevel2 = 22,                  // Mwcb Level2
    MwcbLevel3 = 23,                  // Mwcb Level3
    AuctionCollarReferencePrice = 24, // Auction Collar Reference Price
    AuctionCollarUpperPrice = 25,     // Auction Collar Upper Price
    AuctionCollarLowerPrice = 26,     // Auction Collar Lower Price
    VenueSpecificVolume1 = 10001,     // Venue Specific Volume1
    VenueSpecificPrice1 = 10002,      // Venue Specific Price1
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(StatType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, StatType value);

} // namespace databento::marketdata::normalized::dbn::v3
