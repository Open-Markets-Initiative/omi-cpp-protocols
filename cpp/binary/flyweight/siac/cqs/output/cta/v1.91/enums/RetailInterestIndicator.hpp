#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v1_91 {

// When Retail Price Improvement (RPI) interest is priced better than the Protected Best Bid or
// Offer (PBBO) by a minimum of $0.001, an indication of interest on the Bid, Offer, or both
// the Bid and Offer will identify that interest will be eligible to interact with incoming
// Retail Order interest.
enum class RetailInterestIndicator : char {
    NotApplicable = ' ',                            // Not Applicable
    RetailInterestOnBidQuote = 'A',                 // Retail Interest On Bid Quote
    RetailInterestOnOfferQuote = 'B',               // Retail Interest On Offer Quote
    RetailInterestOnBothTheBidAndOfferQuotes = 'C', // Retail Interest On Both The Bid And Offer Quotes
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RetailInterestIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RetailInterestIndicator value);

} // namespace siac::cqs::output::cta::v1_91
