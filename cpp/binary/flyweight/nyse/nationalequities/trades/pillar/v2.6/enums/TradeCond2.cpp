#include "TradeCond2.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

std::string_view to_string(TradeCond2 value) {
    switch (value) {
        case TradeCond2::Na: return "Na";
        case TradeCond2::IntermarketSweepOrder: return "Intermarket Sweep Order";
        case TradeCond2::MarketCenterOpeningTrade: return "Market Center Opening Trade";
        case TradeCond2::DerivativelyPricedTrfOnly: return "Derivatively Priced Trf Only";
        case TradeCond2::ReopeningTrade: return "Reopening Trade";
        case TradeCond2::MarketCenterClosingTrade: return "Market Center Closing Trade";
        case TradeCond2::QualifiedContingentTradeTrfOrTexasOnly: return "Qualified Contingent Trade Trf Or Texas Only";
        case TradeCond2::CorrectedConsolidatedClose: return "Corrected Consolidated Close";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCond2 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
