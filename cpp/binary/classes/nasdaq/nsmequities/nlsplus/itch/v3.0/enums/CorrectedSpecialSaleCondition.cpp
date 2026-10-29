#include "CorrectedSpecialSaleCondition.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(CorrectedSpecialSaleCondition value) {
    switch (value) {
        case CorrectedSpecialSaleCondition::Acquisition: return "Acquisition";
        case CorrectedSpecialSaleCondition::Bunched: return "Bunched";
        case CorrectedSpecialSaleCondition::Distribution: return "Distribution";
        case CorrectedSpecialSaleCondition::PriceVariationTransaction: return "Price Variation Transaction";
        case CorrectedSpecialSaleCondition::NasdaqOfficialClosePrice: return "Nasdaq Official Close Price";
        case CorrectedSpecialSaleCondition::PriorReferencePrice: return "Prior Reference Price";
        case CorrectedSpecialSaleCondition::NasdaqOfficialOpeningPrice: return "Nasdaq Official Opening Price";
        case CorrectedSpecialSaleCondition::SplitTrade: return "Split Trade";
        case CorrectedSpecialSaleCondition::ContingentTrade: return "Contingent Trade";
        case CorrectedSpecialSaleCondition::AveragePriceTrade: return "Average Price Trade";
        case CorrectedSpecialSaleCondition::CrossTrade: return "Cross Trade";
        case CorrectedSpecialSaleCondition::OddLotExecution: return "Odd Lot Execution";
        case CorrectedSpecialSaleCondition::OddLotCrossExecution: return "Odd Lot Cross Execution";
        case CorrectedSpecialSaleCondition::NotApplicable: return "Not Applicable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CorrectedSpecialSaleCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
