#include "NationalBboLuldIndicator.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(NationalBboLuldIndicator value) {
    switch (value) {
        case NationalBboLuldIndicator::LimitUpLimitDownNotApplicable: return "Limit Up Limit Down Not Applicable";
        case NationalBboLuldIndicator::NationalBestBidAndorNationalBestOfferAreExecutable: return "National Best Bid Andor National Best Offer Are Executable";
        case NationalBboLuldIndicator::NationalBestBidBelowLowerLimitPriceBand: return "National Best Bid Below Lower Limit Price Band";
        case NationalBboLuldIndicator::NationalBestOfferAboveUpperLimitPriceBand: return "National Best Offer Above Upper Limit Price Band";
        case NationalBboLuldIndicator::NationalBestBidBelowLowerAndNationalBestOfferAboveUpperLimitPriceBand: return "National Best Bid Below Lower And National Best Offer Above Upper Limit Price Band";
        case NationalBboLuldIndicator::NationalBestBidEqualsUpperLimitPriceBand: return "National Best Bid Equals Upper Limit Price Band";
        case NationalBboLuldIndicator::NationalBestOfferEqualsLowerLimitPriceBand: return "National Best Offer Equals Lower Limit Price Band";
        case NationalBboLuldIndicator::NationalBestBidInLimitStateAndNationalBestOfferNonExecutable: return "National Best Bid In Limit State And National Best Offer Non Executable";
        case NationalBboLuldIndicator::NationalBestBidNonExecutableAndNationalBestOfferInLimitState: return "National Best Bid Non Executable And National Best Offer In Limit State";
        case NationalBboLuldIndicator::NationalBestBidEqualsUpperAndNationalBestOfferEqualsLowerLimitPriceBand: return "National Best Bid Equals Upper And National Best Offer Equals Lower Limit Price Band";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, NationalBboLuldIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v2_10_a
