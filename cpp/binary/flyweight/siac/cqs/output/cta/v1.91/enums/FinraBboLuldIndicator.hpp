#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v1_91 {

// Indicates the affect that the Limit Up-Limit Down Price Bands have on the FINRA Best Bid and
// FINRA Best Offer
enum class FinraBboLuldIndicator : char {
    LimitUpLimitDownNotApplicable = ' ',                                                                                  // Limit Up Limit Down Not Applicable
    FinraBestBidAndOrFinraBestOfferAreExecutable = 'A',                                                                   // Finra Best Bid And Or Finra Best Offer Are Executable
    FinraBestBidBelowLowerLimitPriceBandAndFinraBestBidIsNonExecutable = 'B',                                             // Finra Best Bid Below Lower Limit Price Band And Finra Best Bid Is Non Executable
    FinraBestOfferAboveUpperLimitPriceBandAndFinraBestOfferIsNonExecutable = 'C',                                         // Finra Best Offer Above Upper Limit Price Band And Finra Best Offer Is Non Executable
    BestBidBelowLowerLimitPriceBandAndBestOfferAboveUpperLimitPriceBandBestBidAndBestOfferAreNonExecutableForFinra = 'D', // Best Bid Below Lower Limit Price Band And Best Offer Above Upper Limit Price Band Best Bid And Best Offer Are Non Executable For Finra
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(FinraBboLuldIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, FinraBboLuldIndicator value);

} // namespace siac::cqs::output::cta::v1_91
