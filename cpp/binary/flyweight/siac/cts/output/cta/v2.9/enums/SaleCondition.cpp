#include "SaleCondition.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(SaleCondition value) {
    switch (value) {
        case SaleCondition::RegularSale: return "Regular Sale";
        case SaleCondition::AveragePriceTrade: return "Average Price Trade";
        case SaleCondition::CashTrade: return "Cash Trade";
        case SaleCondition::AutomaticExecution: return "Automatic Execution";
        case SaleCondition::IntermarketSweepOrder: return "Intermarket Sweep Order";
        case SaleCondition::PriceVariationTrade: return "Price Variation Trade";
        case SaleCondition::OddLotTrade: return "Odd Lot Trade";
        case SaleCondition::Rule127Or155: return "Rule 127 Or 155";
        case SaleCondition::SoldLast: return "Sold Last";
        case SaleCondition::MarketCenterOfficialClose: return "Market Center Official Close";
        case SaleCondition::NextDayTrade: return "Next Day Trade";
        case SaleCondition::MarketCenterOpeningTrade: return "Market Center Opening Trade";
        case SaleCondition::PriorReferencePrice: return "Prior Reference Price";
        case SaleCondition::MarketCenterOfficialOpen: return "Market Center Official Open";
        case SaleCondition::Seller: return "Seller";
        case SaleCondition::ExtendedHoursTrade: return "Extended Hours Trade";
        case SaleCondition::ExtendedHoursSold: return "Extended Hours Sold";
        case SaleCondition::ContingentTrade: return "Contingent Trade";
        case SaleCondition::CrossTrade: return "Cross Trade";
        case SaleCondition::Sold: return "Sold";
        case SaleCondition::DerivativelyPriced: return "Derivatively Priced";
        case SaleCondition::MarketCenterReopeningTrade: return "Market Center Reopening Trade";
        case SaleCondition::MarketCenterClosingTrade: return "Market Center Closing Trade";
        case SaleCondition::QualifiedContingentTrade: return "Qualified Contingent Trade";
        case SaleCondition::Reserved: return "Reserved";
        case SaleCondition::CorrectedConsolidatedClosePriceAsPerListingMarket: return "Corrected Consolidated Close Price As Per Listing Market";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SaleCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
