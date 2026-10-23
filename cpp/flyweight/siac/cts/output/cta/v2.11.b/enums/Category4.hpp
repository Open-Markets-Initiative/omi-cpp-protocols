#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// SRO Trade Detail
enum class Category4 : char {
    NoSroRequiredTradeDetail = ' ',                 // No Sro Required Trade Detail
    AveragePriceTrade = 'B',                        // Average Price Trade
    AutomaticExecution = 'E',                       // Automatic Execution
    PriceVariationTrade = 'H',                      // Price Variation Trade
    OddLotTrade = 'I',                              // Odd Lot Trade
    Rule127NyseOnlyOrRule155NyseAmericanOnly = 'K', // Rule 127 Nyse Only Or Rule 155 Nyse American Only
    MarketCenterOfficialClose = 'M',                // Market Center Official Close
    PriorReferencePrice = 'P',                      // Prior Reference Price
    MarketCenterOfficialOpen = 'Q',                 // Market Center Official Open
    ContingentTrade = 'V',                          // Contingent Trade
    CrossPeriodicAuctionTrade = 'X',                // Cross Periodic Auction Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Category4 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Category4 value);

} // namespace siac::cts::output::cta::v2_11_b
