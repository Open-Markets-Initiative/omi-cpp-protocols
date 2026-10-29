#include "LimitUpLimitDownIndicator.hpp"

namespace siac::cts::output::cta::v2_10 {

std::string_view to_string(LimitUpLimitDownIndicator value) {
    switch (value) {
        case LimitUpLimitDownIndicator::NotApplicable: return "Not Applicable";
        case LimitUpLimitDownIndicator::LimitUpLimitDownPriceBand: return "Limit Up Limit Down Price Band";
        case LimitUpLimitDownIndicator::RepublishedLimitUpLimitDownPriceBand: return "Republished Limit Up Limit Down Price Band";
        case LimitUpLimitDownIndicator::NationalBestBidLimitStateEntered: return "National Best Bid Limit State Entered";
        case LimitUpLimitDownIndicator::NationalBestBidLimitStateExited: return "National Best Bid Limit State Exited";
        case LimitUpLimitDownIndicator::NationalBestOfferLimitStateEntered: return "National Best Offer Limit State Entered";
        case LimitUpLimitDownIndicator::NationalBestOfferLimitStateExited: return "National Best Offer Limit State Exited";
        case LimitUpLimitDownIndicator::NationalBestBidAndNationalBestOfferLimitStateEntered: return "National Best Bid And National Best Offer Limit State Entered";
        case LimitUpLimitDownIndicator::NationalBestBidAndNationalBestOfferLimitStateExited: return "National Best Bid And National Best Offer Limit State Exited";
        case LimitUpLimitDownIndicator::NationalBestBidLimitStateEnteredAndNationalBestOfferLimitStateExited: return "National Best Bid Limit State Entered And National Best Offer Limit State Exited";
        case LimitUpLimitDownIndicator::NationalBestBidLimitStateExitedAndNationalBestOfferLimitStateEntered: return "National Best Bid Limit State Exited And National Best Offer Limit State Entered";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LimitUpLimitDownIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_10
