#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nationalequities::trades::pillar::v2_6 {

// The reason for Trade Through Exemptions.
enum class TradeCond2 : char {
    Na = ' ',                                     // Na
    IntermarketSweepOrder = 'F',                  // Intermarket Sweep Order
    MarketCenterOpeningTrade = 'O',               // Market Center Opening Trade
    DerivativelyPricedTrfOnly = '4',              // Derivatively Priced Trf Only
    ReopeningTrade = '5',                         // Reopening Trade
    MarketCenterClosingTrade = '6',               // Market Center Closing Trade
    QualifiedContingentTradeTrfOrTexasOnly = '7', // Qualified Contingent Trade Trf Or Texas Only
    CorrectedConsolidatedClose = '9',             // Corrected Consolidated Close
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCond2 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCond2 value);

} // namespace nyse::nationalequities::trades::pillar::v2_6
