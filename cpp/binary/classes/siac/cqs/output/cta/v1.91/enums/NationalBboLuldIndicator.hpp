#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v1_91 {

// Indicates the affect that the Limit Up-Limit Down Price Band changes have on the National
// Best Bid and National Best Offer
enum class NationalBboLuldIndicator : char {
    NotApplicable = ' ',                                                                                                           // Not Applicable
    NationalBestBidAndOrNationalBestOfferAreExecutable = 'A',                                                                      // National Best Bid And Or National Best Offer Are Executable
    NationalBestBidBelowLowerLimitPriceBandAndIsNonExecutable = 'B',                                                               // National Best Bid Below Lower Limit Price Band And Is Non Executable
    NationalBestOfferAboveUpperLimitPriceBandAndIsNonExecutable = 'C',                                                             // National Best Offer Above Upper Limit Price Band And Is Non Executable
    NationalBestBidBelowLowerLimitPriceBandAndNationalBestOfferAboveUpperLimitPriceBandBothAreNonExecutable = 'D',                 // National Best Bid Below Lower Limit Price Band And National Best Offer Above Upper Limit Price Band Both Are Non Executable
    NationalBestBidEqualsUpperLimitPriceBandAndIsInLimitState = 'E',                                                               // National Best Bid Equals Upper Limit Price Band And Is In Limit State
    NationalBestOfferEqualsLowerLimitPriceBandAndIsInLimitState = 'F',                                                             // National Best Offer Equals Lower Limit Price Band And Is In Limit State
    NationalBestBidEqualsUpperLimitPriceBandAndIsInLimitStateAndNationalBestOfferAboveUpperLimitPriceBandAndIsNonExecutable = 'G', // National Best Bid Equals Upper Limit Price Band And Is In Limit State And National Best Offer Above Upper Limit Price Band And Is Non Executable
    NationalBestBidBelowLowerLimitPriceBandAndIsNonExecutableAndNationalBestOfferEqualsLowerLimitPriceBandAndIsInLimitState = 'H', // National Best Bid Below Lower Limit Price Band And Is Non Executable And National Best Offer Equals Lower Limit Price Band And Is In Limit State
    NationalBestBidEqualsUpperLimitPriceBandAndNationalBestOfferEqualsLowerLimitPriceBand = 'I',                                   // National Best Bid Equals Upper Limit Price Band And National Best Offer Equals Lower Limit Price Band
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(NationalBboLuldIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, NationalBboLuldIndicator value);

} // namespace siac::cqs::output::cta::v1_91
