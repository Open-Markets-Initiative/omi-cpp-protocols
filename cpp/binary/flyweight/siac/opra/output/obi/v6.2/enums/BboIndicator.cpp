#include "BboIndicator.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(BboIndicator value) {
    switch (value) {
        case BboIndicator::NoBestBidChangeOrBestOfferChange: return "No Best Bid Change Or Best Offer Change";
        case BboIndicator::NoBestBidChangeQuoteContainsBestOffer: return "No Best Bid Change Quote Contains Best Offer";
        case BboIndicator::NoBestBidChangeBestOfferAppendage: return "No Best Bid Change Best Offer Appendage";
        case BboIndicator::NoBestBidChangeNoBestOffer: return "No Best Bid Change No Best Offer";
        case BboIndicator::QuoteContainsBestBidNoBestOfferChange: return "Quote Contains Best Bid No Best Offer Change";
        case BboIndicator::QuoteContainsBestBidQuoteContainsBestOffer: return "Quote Contains Best Bid Quote Contains Best Offer";
        case BboIndicator::QuoteContainsBestBidBestOfferAppendage: return "Quote Contains Best Bid Best Offer Appendage";
        case BboIndicator::QuoteContainsBestBidNoBestOffer: return "Quote Contains Best Bid No Best Offer";
        case BboIndicator::NoBestBidNoBestOfferChange: return "No Best Bid No Best Offer Change";
        case BboIndicator::NoBestBidQuoteContainsBestOffer: return "No Best Bid Quote Contains Best Offer";
        case BboIndicator::NoBestBidBestOfferAppendage: return "No Best Bid Best Offer Appendage";
        case BboIndicator::NoBestBidNoBestOffer: return "No Best Bid No Best Offer";
        case BboIndicator::BestBidAppendageNoBestOfferChange: return "Best Bid Appendage No Best Offer Change";
        case BboIndicator::BestBidAppendageQuoteContainsBestOffer: return "Best Bid Appendage Quote Contains Best Offer";
        case BboIndicator::BestBidAppendageBestOfferAppendage: return "Best Bid Appendage Best Offer Appendage";
        case BboIndicator::BestBidAppendageNoBestOffer: return "Best Bid Appendage No Best Offer";
        case BboIndicator::NotIncludedInTheBbo: return "Not Included In The Bbo";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BboIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
