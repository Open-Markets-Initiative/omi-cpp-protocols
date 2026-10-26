#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v2_10_a {

// Indicates the effect that the Limit Up-Limit Down Price Band changes have on the National
// Best Bid and National Best Offer
enum class NationalBboLuldIndicator : char {
    LimitUpLimitDownNotApplicable = ' ',                                           // Limit Up Limit Down Not Applicable
    NationalBestBidAndorNationalBestOfferAreExecutable = 'A',                      // National Best Bid Andor National Best Offer Are Executable
    NationalBestBidBelowLowerLimitPriceBand = 'B',                                 // National Best Bid Below Lower Limit Price Band
    NationalBestOfferAboveUpperLimitPriceBand = 'C',                               // National Best Offer Above Upper Limit Price Band
    NationalBestBidBelowLowerAndNationalBestOfferAboveUpperLimitPriceBand = 'D',   // National Best Bid Below Lower And National Best Offer Above Upper Limit Price Band
    NationalBestBidEqualsUpperLimitPriceBand = 'E',                                // National Best Bid Equals Upper Limit Price Band
    NationalBestOfferEqualsLowerLimitPriceBand = 'F',                              // National Best Offer Equals Lower Limit Price Band
    NationalBestBidInLimitStateAndNationalBestOfferNonExecutable = 'G',            // National Best Bid In Limit State And National Best Offer Non Executable
    NationalBestBidNonExecutableAndNationalBestOfferInLimitState = 'H',            // National Best Bid Non Executable And National Best Offer In Limit State
    NationalBestBidEqualsUpperAndNationalBestOfferEqualsLowerLimitPriceBand = 'I', // National Best Bid Equals Upper And National Best Offer Equals Lower Limit Price Band
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(NationalBboLuldIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, NationalBboLuldIndicator value);

} // namespace siac::cqs::output::cta::v2_10_a
