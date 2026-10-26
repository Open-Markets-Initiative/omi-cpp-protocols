#include "LimitUpLimitDownLuldIndicator.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(LimitUpLimitDownLuldIndicator value) {
    switch (value) {
        case LimitUpLimitDownLuldIndicator::LimitUpLimitDownNotApplicable: return "Limit Up Limit Down Not Applicable";
        case LimitUpLimitDownLuldIndicator::BidPriceAboveUpperLimitPriceBand: return "Bid Price Above Upper Limit Price Band";
        case LimitUpLimitDownLuldIndicator::OfferPriceBelowLowerLimitPriceBand: return "Offer Price Below Lower Limit Price Band";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LimitUpLimitDownLuldIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v2_10_a
