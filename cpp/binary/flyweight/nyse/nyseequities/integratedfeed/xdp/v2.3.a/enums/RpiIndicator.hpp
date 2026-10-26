#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// The side(s) where Retail Price Improvement orders (RPI orders) exist.
enum class RpiIndicator : char {
    NoRetailInterest = ' ',                    // No Retail Interest
    RetailInterestOnTheBidSide = 'A',          // Retail Interest On The Bid Side
    RetailInterestOnTheOfferSide = 'B',        // Retail Interest On The Offer Side
    RetailInterestOnTheBidAndOfferSides = 'C', // Retail Interest On The Bid And Offer Sides
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RpiIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RpiIndicator value);

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
