#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

// Category 4: SRO Trade Detail
enum class SroTradeDetail : char {
    NoSroRequiredTradeDetail = ' ',  // No Sro Required Trade Detail
    AveragePriceTrade = 'B',         // Average Price Trade
    AutomaticExecution = 'E',        // Automatic Execution
    PriceVariationTrade = 'H',       // Price Variation Trade
    OddLotTrade = 'I',               // Odd Lot Trade
    Rule127Or155 = 'K',              // Rule 127 Or 155
    MarketCenterOfficialClose = 'M', // Market Center Official Close
    PriorReferencePrice = 'P',       // Prior Reference Price
    MarketCenterOfficialOpen = 'Q',  // Market Center Official Open
    ContingentTrade = 'V',           // Contingent Trade
    CrossTrade = 'X',                // Cross Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SroTradeDetail value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SroTradeDetail value);

} // namespace siac::cts::output::cta::v2_10
