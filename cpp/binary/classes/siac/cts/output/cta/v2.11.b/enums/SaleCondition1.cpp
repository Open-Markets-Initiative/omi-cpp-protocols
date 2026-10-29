#include "SaleCondition1.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(SaleCondition1 value) {
    switch (value) {
        case SaleCondition1::RegularSale: return "Regular Sale";
        case SaleCondition1::AveragePriceTrade: return "Average Price Trade";
        case SaleCondition1::CashTradeSameDayClearing: return "Cash Trade Same Day Clearing";
        case SaleCondition1::AutomaticExecution: return "Automatic Execution";
        case SaleCondition1::InterMarketSweepOrder: return "Inter Market Sweep Order";
        case SaleCondition1::PriceVariationTrade: return "Price Variation Trade";
        case SaleCondition1::OddLotTrade: return "Odd Lot Trade";
        case SaleCondition1::Rule127NyseOnlyOrRule155NyseAmericanOnly: return "Rule 127 Nyse Only Or Rule 155 Nyse American Only";
        case SaleCondition1::SoldLastLateReporting: return "Sold Last Late Reporting";
        case SaleCondition1::MarketCenterOfficialClose: return "Market Center Official Close";
        case SaleCondition1::ReservedN: return "Reserved N";
        case SaleCondition1::MarketCenterOpeningTrade: return "Market Center Opening Trade";
        case SaleCondition1::PriorReferencePrice: return "Prior Reference Price";
        case SaleCondition1::MarketCenterOfficialOpen: return "Market Center Official Open";
        case SaleCondition1::Seller: return "Seller";
        case SaleCondition1::ExtendedHoursTrade: return "Extended Hours Trade";
        case SaleCondition1::ExtendedHoursSoldOutOfSequence: return "Extended Hours Sold Out Of Sequence";
        case SaleCondition1::ContingentTrade: return "Contingent Trade";
        case SaleCondition1::CrossPeriodicAuctionTrade: return "Cross Periodic Auction Trade";
        case SaleCondition1::SoldOutOfSequence: return "Sold Out Of Sequence";
        case SaleCondition1::DerivativelyPriced: return "Derivatively Priced";
        case SaleCondition1::MarketCenterReopeningTrade: return "Market Center Reopening Trade";
        case SaleCondition1::MarketCenterClosingTrade: return "Market Center Closing Trade";
        case SaleCondition1::QualifiedContingentTrade: return "Qualified Contingent Trade";
        case SaleCondition1::Reserved8: return "Reserved 8";
        case SaleCondition1::CorrectedConsolidatedClosePriceAsPerListingMarket: return "Corrected Consolidated Close Price As Per Listing Market";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SaleCondition1 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
