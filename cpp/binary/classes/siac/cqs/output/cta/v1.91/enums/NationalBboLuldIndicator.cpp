#include "NationalBboLuldIndicator.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(NationalBboLuldIndicator value) {
    switch (value) {
        case NationalBboLuldIndicator::NotApplicable: return "Not Applicable";
        case NationalBboLuldIndicator::NationalBestBidAndOrNationalBestOfferAreExecutable: return "National Best Bid And Or National Best Offer Are Executable";
        case NationalBboLuldIndicator::NationalBestBidBelowLowerLimitPriceBandAndIsNonExecutable: return "National Best Bid Below Lower Limit Price Band And Is Non Executable";
        case NationalBboLuldIndicator::NationalBestOfferAboveUpperLimitPriceBandAndIsNonExecutable: return "National Best Offer Above Upper Limit Price Band And Is Non Executable";
        case NationalBboLuldIndicator::NationalBestBidBelowLowerLimitPriceBandAndNationalBestOfferAboveUpperLimitPriceBandBothAreNonExecutable: return "National Best Bid Below Lower Limit Price Band And National Best Offer Above Upper Limit Price Band Both Are Non Executable";
        case NationalBboLuldIndicator::NationalBestBidEqualsUpperLimitPriceBandAndIsInLimitState: return "National Best Bid Equals Upper Limit Price Band And Is In Limit State";
        case NationalBboLuldIndicator::NationalBestOfferEqualsLowerLimitPriceBandAndIsInLimitState: return "National Best Offer Equals Lower Limit Price Band And Is In Limit State";
        case NationalBboLuldIndicator::NationalBestBidEqualsUpperLimitPriceBandAndIsInLimitStateAndNationalBestOfferAboveUpperLimitPriceBandAndIsNonExecutable: return "National Best Bid Equals Upper Limit Price Band And Is In Limit State And National Best Offer Above Upper Limit Price Band And Is Non Executable";
        case NationalBboLuldIndicator::NationalBestBidBelowLowerLimitPriceBandAndIsNonExecutableAndNationalBestOfferEqualsLowerLimitPriceBandAndIsInLimitState: return "National Best Bid Below Lower Limit Price Band And Is Non Executable And National Best Offer Equals Lower Limit Price Band And Is In Limit State";
        case NationalBboLuldIndicator::NationalBestBidEqualsUpperLimitPriceBandAndNationalBestOfferEqualsLowerLimitPriceBand: return "National Best Bid Equals Upper Limit Price Band And National Best Offer Equals Lower Limit Price Band";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, NationalBboLuldIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
