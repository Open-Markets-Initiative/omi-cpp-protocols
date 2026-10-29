#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nationalequities::bbo::pillar::v2_5_d {

// The side(s) where Retail Price Indication orders (RPI orders) exist. Values correspond to
// CQS values.
enum class RpiIndicator : char {
    NoRetailInterestDefault = ' ',            // No Retail Interest Default
    RetailInterestOnBidSide = 'A',            // Retail Interest On Bid Side
    RetailInterestOnOfferSide = 'B',          // Retail Interest On Offer Side
    RetailInterestOnTheBidAndOfferSide = 'C', // Retail Interest On The Bid And Offer Side
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RpiIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RpiIndicator value);

} // namespace nyse::nationalequities::bbo::pillar::v2_5_d
