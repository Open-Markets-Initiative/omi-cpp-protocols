#include "FinraBboLuldIndicator.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(FinraBboLuldIndicator value) {
    switch (value) {
        case FinraBboLuldIndicator::LimitUpLimitDownNotApplicable: return "Limit Up Limit Down Not Applicable";
        case FinraBboLuldIndicator::FinraBestBidAndOrFinraBestOfferAreExecutable: return "Finra Best Bid And Or Finra Best Offer Are Executable";
        case FinraBboLuldIndicator::FinraBestBidBelowLowerLimitPriceBandAndFinraBestBidIsNonExecutable: return "Finra Best Bid Below Lower Limit Price Band And Finra Best Bid Is Non Executable";
        case FinraBboLuldIndicator::FinraBestOfferAboveUpperLimitPriceBandAndFinraBestOfferIsNonExecutable: return "Finra Best Offer Above Upper Limit Price Band And Finra Best Offer Is Non Executable";
        case FinraBboLuldIndicator::BestBidBelowLowerLimitPriceBandAndBestOfferAboveUpperLimitPriceBandBestBidAndBestOfferAreNonExecutableForFinra: return "Best Bid Below Lower Limit Price Band And Best Offer Above Upper Limit Price Band Best Bid And Best Offer Are Non Executable For Finra";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, FinraBboLuldIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
