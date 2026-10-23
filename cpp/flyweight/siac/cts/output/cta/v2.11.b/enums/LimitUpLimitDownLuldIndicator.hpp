#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the Limit Up-Limit Down action related to a security
enum class LimitUpLimitDownLuldIndicator : char {
    LimitUpLimitDownNotApplicable = ' ',                                        // Limit Up Limit Down Not Applicable
    LimitUpLimitDownPriceBand = 'A',                                            // Limit Up Limit Down Price Band
    RepublishedLimitUpLimitDownPriceBand = 'B',                                 // Republished Limit Up Limit Down Price Band
    NationalBestBidLimitStateEntered = 'C',                                     // National Best Bid Limit State Entered
    NationalBestBidLimitStateExited = 'D',                                      // National Best Bid Limit State Exited
    NationalBestOfferLimitStateEntered = 'E',                                   // National Best Offer Limit State Entered
    NationalBestOfferLimitStateExited = 'F',                                    // National Best Offer Limit State Exited
    NationalBestBidAndNationalBestOfferLimitStateEntered = 'G',                 // National Best Bid And National Best Offer Limit State Entered
    NationalBestBidAndNationalBestOfferLimitStateExited = 'H',                  // National Best Bid And National Best Offer Limit State Exited
    NationalBestBidLimitStateEnteredAndNationalBestOfferLimitStateExited = 'I', // National Best Bid Limit State Entered And National Best Offer Limit State Exited
    NationalBestBidLimitStateExitedAndNationalBestOfferLimitStateEntered = 'J', // National Best Bid Limit State Exited And National Best Offer Limit State Entered
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LimitUpLimitDownLuldIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LimitUpLimitDownLuldIndicator value);

} // namespace siac::cts::output::cta::v2_11_b
