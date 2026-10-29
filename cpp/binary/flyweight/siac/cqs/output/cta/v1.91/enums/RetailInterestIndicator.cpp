#include "RetailInterestIndicator.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(RetailInterestIndicator value) {
    switch (value) {
        case RetailInterestIndicator::NotApplicable: return "Not Applicable";
        case RetailInterestIndicator::RetailInterestOnBidQuote: return "Retail Interest On Bid Quote";
        case RetailInterestIndicator::RetailInterestOnOfferQuote: return "Retail Interest On Offer Quote";
        case RetailInterestIndicator::RetailInterestOnBothTheBidAndOfferQuotes: return "Retail Interest On Both The Bid And Offer Quotes";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RetailInterestIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
