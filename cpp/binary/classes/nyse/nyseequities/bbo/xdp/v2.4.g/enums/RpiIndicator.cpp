#include "RpiIndicator.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

std::string_view to_string(RpiIndicator value) {
    switch (value) {
        case RpiIndicator::NoRetailInterest: return "No Retail Interest";
        case RpiIndicator::RetailInterestOnBidSide: return "Retail Interest On Bid Side";
        case RpiIndicator::RetailInterestOnOfferSide: return "Retail Interest On Offer Side";
        case RpiIndicator::RetailInterestOnTheBidAndOfferSide: return "Retail Interest On The Bid And Offer Side";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RpiIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
