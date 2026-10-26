#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v2_10_a {

// Denotes a particular condition applicable to the quote used to determine whether a quote
// qualifies for the Best Bid and Best Offer calculation
enum class QuoteCondition : char {
    QuoteConditionNotApplicable = ' ',               // Quote Condition Not Applicable
    SlowQuoteOnOfferSide = 'A',                      // Slow Quote On Offer Side
    SlowQuoteOnBidSide = 'B',                        // Slow Quote On Bid Side
    Closing = 'C',                                   // Closing
    SlowQuoteDueToLrpOrGapQuoteOnTheBidSide = 'E',   // Slow Quote Due To Lrp Or Gap Quote On The Bid Side
    SlowQuoteDueToLrpOrGapQuoteOnTheOfferSide = 'F', // Slow Quote Due To Lrp Or Gap Quote On The Offer Side
    SlowQuoteOnTheBidAndOfferSides = 'H',            // Slow Quote On The Bid And Offer Sides
    ClosedMarketMaker = 'L',                         // Closed Market Maker
    NonFirmQuote = 'N',                              // Non Firm Quote
    OpeningQuote = 'O',                              // Opening Quote
    Regular = 'R',                                   // Regular
    SlowQuoteDueToLrpOrGapQuoteOnBothSides = 'U',    // Slow Quote Due To Lrp Or Gap Quote On Both Sides
    SlowQuoteDueToSetSlowListOnBothSides = 'W',      // Slow Quote Due To Set Slow List On Both Sides
    OnDemandIntraDayAuction = '4',                   // On Demand Intra Day Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(QuoteCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, QuoteCondition value);

} // namespace siac::cqs::output::cta::v2_10_a
