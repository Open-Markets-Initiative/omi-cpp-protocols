#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v2_10_a {

// Identifies Retail Price Improvement interest priced better than the Protected Best Bid or
// Offer by a minimum of $0.001
enum class RetailInterestIndicator : char {
    RetailInterestIndicatorNotApplicable = ' ',     // Retail Interest Indicator Not Applicable
    RetailInterestOnBidQuote = 'A',                 // Retail Interest On Bid Quote
    RetailInterestOnOfferQuote = 'B',               // Retail Interest On Offer Quote
    RetailInterestOnBothTheBidAndOfferQuotes = 'C', // Retail Interest On Both The Bid And Offer Quotes
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RetailInterestIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RetailInterestIndicator value);

} // namespace siac::cqs::output::cta::v2_10_a
