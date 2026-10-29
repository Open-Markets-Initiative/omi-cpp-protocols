#include "TradeCond2.hpp"

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {

std::string_view to_string(TradeCond2 value) {
    switch (value) {
        case TradeCond2::Na: return "Na";
        case TradeCond2::IntermarketSweepOrder: return "Intermarket Sweep Order";
        case TradeCond2::MarketCenterOpeningTradeArcaAmericanAndNyseOnly: return "Market Center Opening Trade Arca American And Nyse Only";
        case TradeCond2::ReopeningTradeArcaAmericanAndNyseOnly: return "Reopening Trade Arca American And Nyse Only";
        case TradeCond2::MarketCenterClosingTradeArcaAmericanAndNyseOnly: return "Market Center Closing Trade Arca American And Nyse Only";
        case TradeCond2::QualifiedContingentTradeTexasOnly: return "Qualified Contingent Trade Texas Only";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCond2 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::amexequities::integratedfeed::pillar::v2_5_g
