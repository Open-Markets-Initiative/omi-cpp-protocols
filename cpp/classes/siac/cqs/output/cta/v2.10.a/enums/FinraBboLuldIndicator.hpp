#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v2_10_a {

// Indicates the effect that the Limit Up-Limit Down Price Bands have on the FINRA Best Bid and
// FINRA Best Offer
enum class FinraBboLuldIndicator : char {
    LimitUpLimitDownNotApplicable = ' ',                 // Limit Up Limit Down Not Applicable
    FinraBestBidAndFinraBestOfferAreExecutable = 'A',    // Finra Best Bid And Finra Best Offer Are Executable
    FinraBestBidOutsidePriceBand = 'B',                  // Finra Best Bid Outside Price Band
    FinraBestOfferOutsidePriceBand = 'C',                // Finra Best Offer Outside Price Band
    FinraBestBidAndFinraBestOfferOutsidePriceBand = 'D', // Finra Best Bid And Finra Best Offer Outside Price Band
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(FinraBboLuldIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, FinraBboLuldIndicator value);

} // namespace siac::cqs::output::cta::v2_10_a
