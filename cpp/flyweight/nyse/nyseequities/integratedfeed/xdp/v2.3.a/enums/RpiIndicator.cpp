#include "RpiIndicator.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

std::string_view to_string(RpiIndicator value) {
    switch (value) {
        case RpiIndicator::NoRetailInterest: return "No Retail Interest";
        case RpiIndicator::RetailInterestOnTheBidSide: return "Retail Interest On The Bid Side";
        case RpiIndicator::RetailInterestOnTheOfferSide: return "Retail Interest On The Offer Side";
        case RpiIndicator::RetailInterestOnTheBidAndOfferSides: return "Retail Interest On The Bid And Offer Sides";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RpiIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
