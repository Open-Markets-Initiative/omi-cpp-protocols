#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v2_10_a {

// Indicates the effect the Quote has on the Limit Up-Limit Down Price Band range
enum class LimitUpLimitDownLuldIndicator : char {
    LimitUpLimitDownNotApplicable = ' ',      // Limit Up Limit Down Not Applicable
    BidPriceAboveUpperLimitPriceBand = 'A',   // Bid Price Above Upper Limit Price Band
    OfferPriceBelowLowerLimitPriceBand = 'B', // Offer Price Below Lower Limit Price Band
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LimitUpLimitDownLuldIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LimitUpLimitDownLuldIndicator value);

} // namespace siac::cqs::output::cta::v2_10_a
