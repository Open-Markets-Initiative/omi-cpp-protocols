#include "Category4.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(Category4 value) {
    switch (value) {
        case Category4::NoSroRequiredTradeDetail: return "No Sro Required Trade Detail";
        case Category4::AveragePriceTrade: return "Average Price Trade";
        case Category4::AutomaticExecution: return "Automatic Execution";
        case Category4::PriceVariationTrade: return "Price Variation Trade";
        case Category4::OddLotTrade: return "Odd Lot Trade";
        case Category4::Rule127Or155: return "Rule 127 Or 155";
        case Category4::MarketCenterOfficialClose: return "Market Center Official Close";
        case Category4::PriorReferencePrice: return "Prior Reference Price";
        case Category4::MarketCenterOfficialOpen: return "Market Center Official Open";
        case Category4::ContingentTrade: return "Contingent Trade";
        case Category4::CrossTrade: return "Cross Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Category4 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v1_91
