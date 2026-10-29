#include "SroTradeDetail.hpp"

namespace siac::cts::output::cta::v2_10 {

std::string_view to_string(SroTradeDetail value) {
    switch (value) {
        case SroTradeDetail::NoSroRequiredTradeDetail: return "No Sro Required Trade Detail";
        case SroTradeDetail::AveragePriceTrade: return "Average Price Trade";
        case SroTradeDetail::AutomaticExecution: return "Automatic Execution";
        case SroTradeDetail::PriceVariationTrade: return "Price Variation Trade";
        case SroTradeDetail::OddLotTrade: return "Odd Lot Trade";
        case SroTradeDetail::Rule127Or155: return "Rule 127 Or 155";
        case SroTradeDetail::MarketCenterOfficialClose: return "Market Center Official Close";
        case SroTradeDetail::PriorReferencePrice: return "Prior Reference Price";
        case SroTradeDetail::MarketCenterOfficialOpen: return "Market Center Official Open";
        case SroTradeDetail::ContingentTrade: return "Contingent Trade";
        case SroTradeDetail::CrossTrade: return "Cross Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SroTradeDetail value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_10
