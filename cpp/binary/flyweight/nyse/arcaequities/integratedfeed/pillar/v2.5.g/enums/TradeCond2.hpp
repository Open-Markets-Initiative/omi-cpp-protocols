#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

// The reason for Trade Through Exemptions.
enum class TradeCond2 : char {
    Na = ' ',                                              // Na
    IntermarketSweepOrder = 'F',                           // Intermarket Sweep Order
    MarketCenterOpeningTradeArcaAmericanAndNyseOnly = 'O', // Market Center Opening Trade Arca American And Nyse Only
    ReopeningTradeArcaAmericanAndNyseOnly = '5',           // Reopening Trade Arca American And Nyse Only
    MarketCenterClosingTradeArcaAmericanAndNyseOnly = '6', // Market Center Closing Trade Arca American And Nyse Only
    QualifiedContingentTradeTexasOnly = '7',               // Qualified Contingent Trade Texas Only
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCond2 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCond2 value);

} // namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g
