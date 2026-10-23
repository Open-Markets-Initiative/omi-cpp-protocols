#include "FinraBboLuldIndicator.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(FinraBboLuldIndicator value) {
    switch (value) {
        case FinraBboLuldIndicator::LimitUpLimitDownNotApplicable: return "Limit Up Limit Down Not Applicable";
        case FinraBboLuldIndicator::FinraBestBidAndFinraBestOfferAreExecutable: return "Finra Best Bid And Finra Best Offer Are Executable";
        case FinraBboLuldIndicator::FinraBestBidOutsidePriceBand: return "Finra Best Bid Outside Price Band";
        case FinraBboLuldIndicator::FinraBestOfferOutsidePriceBand: return "Finra Best Offer Outside Price Band";
        case FinraBboLuldIndicator::FinraBestBidAndFinraBestOfferOutsidePriceBand: return "Finra Best Bid And Finra Best Offer Outside Price Band";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, FinraBboLuldIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v2_10_a
