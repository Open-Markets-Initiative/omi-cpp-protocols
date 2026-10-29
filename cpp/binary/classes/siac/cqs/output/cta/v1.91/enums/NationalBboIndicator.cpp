#include "NationalBboIndicator.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(NationalBboIndicator value) {
    switch (value) {
        case NationalBboIndicator::NotIncluded: return "Not Included";
        case NationalBboIndicator::NoBestBidChangeOrBestOfferChange: return "No Best Bid Change Or Best Offer Change";
        case NationalBboIndicator::NoBestBidChangeQuoteContainsBestOffer: return "No Best Bid Change Quote Contains Best Offer";
        case NationalBboIndicator::NoBestBidChangeBestOfferShortAppendage: return "No Best Bid Change Best Offer Short Appendage";
        case NationalBboIndicator::NoBestBidChangeBestOfferLongAppendage: return "No Best Bid Change Best Offer Long Appendage";
        case NationalBboIndicator::NoBestBidChangeNoBestOffer: return "No Best Bid Change No Best Offer";
        case NationalBboIndicator::QuoteContainsBestBidNoBestOfferChange: return "Quote Contains Best Bid No Best Offer Change";
        case NationalBboIndicator::QuoteContainsBestBidQuoteContainsBestOffer: return "Quote Contains Best Bid Quote Contains Best Offer";
        case NationalBboIndicator::QuoteContainsBestBidBestOfferShortAppendage: return "Quote Contains Best Bid Best Offer Short Appendage";
        case NationalBboIndicator::QuoteContainsBestBidBestOfferLongAppendage: return "Quote Contains Best Bid Best Offer Long Appendage";
        case NationalBboIndicator::QuoteContainsBestBidNoBestOffer: return "Quote Contains Best Bid No Best Offer";
        case NationalBboIndicator::NoBestBidNoBestOfferChange: return "No Best Bid No Best Offer Change";
        case NationalBboIndicator::NoBestBidQuoteContainsBestOffer: return "No Best Bid Quote Contains Best Offer";
        case NationalBboIndicator::NoBestBidBestOfferShortAppendage: return "No Best Bid Best Offer Short Appendage";
        case NationalBboIndicator::NoBestBidBestOfferLongAppendage: return "No Best Bid Best Offer Long Appendage";
        case NationalBboIndicator::NoBestBidNoBestOffer: return "No Best Bid No Best Offer";
        case NationalBboIndicator::BestBidShortAppendageNoBestOfferChange: return "Best Bid Short Appendage No Best Offer Change";
        case NationalBboIndicator::BestBidLongAppendageNoBestOfferChange: return "Best Bid Long Appendage No Best Offer Change";
        case NationalBboIndicator::BestBidShortAppendageQuoteContainsBestOffer: return "Best Bid Short Appendage Quote Contains Best Offer";
        case NationalBboIndicator::BestBidLongAppendageQuoteContainsBestOffer: return "Best Bid Long Appendage Quote Contains Best Offer";
        case NationalBboIndicator::BestBidShortAppendageBestOfferShortAppendage: return "Best Bid Short Appendage Best Offer Short Appendage";
        case NationalBboIndicator::BestBidLongAppendageBestOfferLongAppendage: return "Best Bid Long Appendage Best Offer Long Appendage";
        case NationalBboIndicator::BestBidShortAppendageNoBestOffer: return "Best Bid Short Appendage No Best Offer";
        case NationalBboIndicator::BestBidLongAppendageNoBestOffer: return "Best Bid Long Appendage No Best Offer";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, NationalBboIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
