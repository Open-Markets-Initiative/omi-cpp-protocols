#include "Category2.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(Category2 value) {
    switch (value) {
        case Category2::NoTradeThroughExemptReason: return "No Trade Through Exempt Reason";
        case Category2::InterMarketSweepOrder: return "Inter Market Sweep Order";
        case Category2::DerivativelyPriced: return "Derivatively Priced";
        case Category2::MarketCenterReopeningTrade: return "Market Center Reopening Trade";
        case Category2::MarketCenterClosingTrade: return "Market Center Closing Trade";
        case Category2::QualifiedContingentTrade: return "Qualified Contingent Trade";
        case Category2::Reserved: return "Reserved";
        case Category2::CorrectedConsolidatedClosePriceAsPerListingMarket: return "Corrected Consolidated Close Price As Per Listing Market";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Category2 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
