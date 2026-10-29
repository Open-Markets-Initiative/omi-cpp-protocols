#include "RpiIndicator.hpp"

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {

std::string_view to_string(RpiIndicator value) {
    switch (value) {
        case RpiIndicator::NoRetailInterestDefault: return "No Retail Interest Default";
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

} // namespace nyse::amexequities::integratedfeed::pillar::v2_5_g
