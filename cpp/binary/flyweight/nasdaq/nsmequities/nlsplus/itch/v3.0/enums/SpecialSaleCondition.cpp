#include "SpecialSaleCondition.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(SpecialSaleCondition value) {
    switch (value) {
        case SpecialSaleCondition::Acquisition: return "Acquisition";
        case SpecialSaleCondition::Bunched: return "Bunched";
        case SpecialSaleCondition::Distribution: return "Distribution";
        case SpecialSaleCondition::PriceVariationTransaction: return "Price Variation Transaction";
        case SpecialSaleCondition::NasdaqOfficialClosePrice: return "Nasdaq Official Close Price";
        case SpecialSaleCondition::PriorReferencePrice: return "Prior Reference Price";
        case SpecialSaleCondition::NasdaqOfficialOpeningPrice: return "Nasdaq Official Opening Price";
        case SpecialSaleCondition::SplitTrade: return "Split Trade";
        case SpecialSaleCondition::ContingentTrade: return "Contingent Trade";
        case SpecialSaleCondition::AveragePriceTrade: return "Average Price Trade";
        case SpecialSaleCondition::CrossTrade: return "Cross Trade";
        case SpecialSaleCondition::OddLotExecution: return "Odd Lot Execution";
        case SpecialSaleCondition::OddLotCrossExecution: return "Odd Lot Cross Execution";
        case SpecialSaleCondition::NotApplicable: return "Not Applicable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SpecialSaleCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
