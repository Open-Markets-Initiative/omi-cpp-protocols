#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_8 {

// Market Data entry type
enum class MdEntryType : char {
    Bid = '0',                                  // Bid
    Offer = '1',                                // Offer
    Trade = '2',                                // Trade
    OpenPrice = '4',                            // Open Price
    SettlementPrice = '6',                      // Settlement Price
    TradingSessionHighPrice = '7',              // Trading Session High Price
    TradingSessionLowPrice = '8',               // Trading Session Low Price
    ClearedVolume = 'B',                        // Cleared Volume
    OpenInterest = 'C',                         // Open Interest
    ImpliedBid = 'E',                           // Implied Bid
    ImpliedOffer = 'F',                         // Implied Offer
    BookReset = 'J',                            // Book Reset
    SessionHighBid = 'N',                       // Session High Bid
    SessionLowOffer = 'O',                      // Session Low Offer
    FixingPrice = 'W',                          // Fixing Price
    ElectronicVolume = 'e',                     // Electronic Volume
    ThresholdLimitsandPriceBandVariation = 'g', // Threshold Limitsand Price Band Variation
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdEntryType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdEntryType value);

} // namespace cme::globex::mdp3::sbe::v1_8
