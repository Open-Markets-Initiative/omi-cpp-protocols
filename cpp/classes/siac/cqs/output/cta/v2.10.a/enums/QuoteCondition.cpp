#include "QuoteCondition.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(QuoteCondition value) {
    switch (value) {
        case QuoteCondition::QuoteConditionNotApplicable: return "Quote Condition Not Applicable";
        case QuoteCondition::SlowQuoteOnOfferSide: return "Slow Quote On Offer Side";
        case QuoteCondition::SlowQuoteOnBidSide: return "Slow Quote On Bid Side";
        case QuoteCondition::Closing: return "Closing";
        case QuoteCondition::SlowQuoteDueToLrpOrGapQuoteOnTheBidSide: return "Slow Quote Due To Lrp Or Gap Quote On The Bid Side";
        case QuoteCondition::SlowQuoteDueToLrpOrGapQuoteOnTheOfferSide: return "Slow Quote Due To Lrp Or Gap Quote On The Offer Side";
        case QuoteCondition::SlowQuoteOnTheBidAndOfferSides: return "Slow Quote On The Bid And Offer Sides";
        case QuoteCondition::ClosedMarketMaker: return "Closed Market Maker";
        case QuoteCondition::NonFirmQuote: return "Non Firm Quote";
        case QuoteCondition::OpeningQuote: return "Opening Quote";
        case QuoteCondition::Regular: return "Regular";
        case QuoteCondition::SlowQuoteDueToLrpOrGapQuoteOnBothSides: return "Slow Quote Due To Lrp Or Gap Quote On Both Sides";
        case QuoteCondition::SlowQuoteDueToSetSlowListOnBothSides: return "Slow Quote Due To Set Slow List On Both Sides";
        case QuoteCondition::OnDemandIntraDayAuction: return "On Demand Intra Day Auction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, QuoteCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v2_10_a
