#include "OriginalSpecialSaleCondition.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(OriginalSpecialSaleCondition value) {
    switch (value) {
        case OriginalSpecialSaleCondition::Acquisition: return "Acquisition";
        case OriginalSpecialSaleCondition::Bunched: return "Bunched";
        case OriginalSpecialSaleCondition::Distribution: return "Distribution";
        case OriginalSpecialSaleCondition::PriceVariationTransaction: return "Price Variation Transaction";
        case OriginalSpecialSaleCondition::NasdaqOfficialClosePrice: return "Nasdaq Official Close Price";
        case OriginalSpecialSaleCondition::PriorReferencePrice: return "Prior Reference Price";
        case OriginalSpecialSaleCondition::NasdaqOfficialOpeningPrice: return "Nasdaq Official Opening Price";
        case OriginalSpecialSaleCondition::SplitTrade: return "Split Trade";
        case OriginalSpecialSaleCondition::ContingentTrade: return "Contingent Trade";
        case OriginalSpecialSaleCondition::AveragePriceTrade: return "Average Price Trade";
        case OriginalSpecialSaleCondition::CrossTrade: return "Cross Trade";
        case OriginalSpecialSaleCondition::OddLotExecution: return "Odd Lot Execution";
        case OriginalSpecialSaleCondition::OddLotCrossExecution: return "Odd Lot Cross Execution";
        case OriginalSpecialSaleCondition::NotApplicable: return "Not Applicable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OriginalSpecialSaleCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
