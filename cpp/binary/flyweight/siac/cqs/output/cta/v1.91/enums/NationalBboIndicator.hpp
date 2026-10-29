#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v1_91 {

// Indicates the affect the new quote has on the National BBO.
enum class NationalBboIndicator : char {
    NotIncluded = ' ',                                  // Not Included
    NoBestBidChangeOrBestOfferChange = 'A',             // No Best Bid Change Or Best Offer Change
    NoBestBidChangeQuoteContainsBestOffer = 'B',        // No Best Bid Change Quote Contains Best Offer
    NoBestBidChangeBestOfferShortAppendage = 'C',       // No Best Bid Change Best Offer Short Appendage
    NoBestBidChangeBestOfferLongAppendage = 'D',        // No Best Bid Change Best Offer Long Appendage
    NoBestBidChangeNoBestOffer = 'E',                   // No Best Bid Change No Best Offer
    QuoteContainsBestBidNoBestOfferChange = 'F',        // Quote Contains Best Bid No Best Offer Change
    QuoteContainsBestBidQuoteContainsBestOffer = 'G',   // Quote Contains Best Bid Quote Contains Best Offer
    QuoteContainsBestBidBestOfferShortAppendage = 'H',  // Quote Contains Best Bid Best Offer Short Appendage
    QuoteContainsBestBidBestOfferLongAppendage = 'I',   // Quote Contains Best Bid Best Offer Long Appendage
    QuoteContainsBestBidNoBestOffer = 'J',              // Quote Contains Best Bid No Best Offer
    NoBestBidNoBestOfferChange = 'K',                   // No Best Bid No Best Offer Change
    NoBestBidQuoteContainsBestOffer = 'L',              // No Best Bid Quote Contains Best Offer
    NoBestBidBestOfferShortAppendage = 'M',             // No Best Bid Best Offer Short Appendage
    NoBestBidBestOfferLongAppendage = 'N',              // No Best Bid Best Offer Long Appendage
    NoBestBidNoBestOffer = 'O',                         // No Best Bid No Best Offer
    BestBidShortAppendageNoBestOfferChange = 'P',       // Best Bid Short Appendage No Best Offer Change
    BestBidLongAppendageNoBestOfferChange = 'Q',        // Best Bid Long Appendage No Best Offer Change
    BestBidShortAppendageQuoteContainsBestOffer = 'R',  // Best Bid Short Appendage Quote Contains Best Offer
    BestBidLongAppendageQuoteContainsBestOffer = 'S',   // Best Bid Long Appendage Quote Contains Best Offer
    BestBidShortAppendageBestOfferShortAppendage = 'T', // Best Bid Short Appendage Best Offer Short Appendage
    BestBidLongAppendageBestOfferLongAppendage = 'U',   // Best Bid Long Appendage Best Offer Long Appendage
    BestBidShortAppendageNoBestOffer = 'V',             // Best Bid Short Appendage No Best Offer
    BestBidLongAppendageNoBestOffer = 'W',              // Best Bid Long Appendage No Best Offer
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(NationalBboIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, NationalBboIndicator value);

} // namespace siac::cqs::output::cta::v1_91
