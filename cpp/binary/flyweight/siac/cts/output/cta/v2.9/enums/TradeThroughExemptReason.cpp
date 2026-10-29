#include "TradeThroughExemptReason.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(TradeThroughExemptReason value) {
    switch (value) {
        case TradeThroughExemptReason::NoReason: return "No Reason";
        case TradeThroughExemptReason::IntermarketSweepOrder: return "Intermarket Sweep Order";
        case TradeThroughExemptReason::MarketCenterOpeningTrade: return "Market Center Opening Trade";
        case TradeThroughExemptReason::DerivativelyPriced: return "Derivatively Priced";
        case TradeThroughExemptReason::MarketCenterReopeningTrade: return "Market Center Reopening Trade";
        case TradeThroughExemptReason::MarketCenterClosingTrade: return "Market Center Closing Trade";
        case TradeThroughExemptReason::QualifiedContingentTrade: return "Qualified Contingent Trade";
        case TradeThroughExemptReason::Reserved: return "Reserved";
        case TradeThroughExemptReason::CorrectedConsolidatedClosePriceAsPerListingMarket: return "Corrected Consolidated Close Price As Per Listing Market";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeThroughExemptReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
