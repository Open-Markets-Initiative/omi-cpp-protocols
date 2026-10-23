#include "LimitUpLimitDownLuldIndicator.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(LimitUpLimitDownLuldIndicator value) {
    switch (value) {
        case LimitUpLimitDownLuldIndicator::LimitUpLimitDownNotApplicable: return "Limit Up Limit Down Not Applicable";
        case LimitUpLimitDownLuldIndicator::LimitUpLimitDownPriceBand: return "Limit Up Limit Down Price Band";
        case LimitUpLimitDownLuldIndicator::RepublishedLimitUpLimitDownPriceBand: return "Republished Limit Up Limit Down Price Band";
        case LimitUpLimitDownLuldIndicator::NationalBestBidLimitStateEntered: return "National Best Bid Limit State Entered";
        case LimitUpLimitDownLuldIndicator::NationalBestBidLimitStateExited: return "National Best Bid Limit State Exited";
        case LimitUpLimitDownLuldIndicator::NationalBestOfferLimitStateEntered: return "National Best Offer Limit State Entered";
        case LimitUpLimitDownLuldIndicator::NationalBestOfferLimitStateExited: return "National Best Offer Limit State Exited";
        case LimitUpLimitDownLuldIndicator::NationalBestBidAndNationalBestOfferLimitStateEntered: return "National Best Bid And National Best Offer Limit State Entered";
        case LimitUpLimitDownLuldIndicator::NationalBestBidAndNationalBestOfferLimitStateExited: return "National Best Bid And National Best Offer Limit State Exited";
        case LimitUpLimitDownLuldIndicator::NationalBestBidLimitStateEnteredAndNationalBestOfferLimitStateExited: return "National Best Bid Limit State Entered And National Best Offer Limit State Exited";
        case LimitUpLimitDownLuldIndicator::NationalBestBidLimitStateExitedAndNationalBestOfferLimitStateEntered: return "National Best Bid Limit State Exited And National Best Offer Limit State Entered";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LimitUpLimitDownLuldIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
