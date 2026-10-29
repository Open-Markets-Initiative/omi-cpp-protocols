#include "RpiIndicator.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

std::string_view to_string(RpiIndicator value) {
    switch (value) {
        case RpiIndicator::NoRetailInterest: return "No Retail Interest";
        case RpiIndicator::InterestOnBid: return "Interest On Bid";
        case RpiIndicator::InterestOnOffer: return "Interest On Offer";
        case RpiIndicator::InterestOnBidAndOffer: return "Interest On Bid And Offer";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RpiIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
