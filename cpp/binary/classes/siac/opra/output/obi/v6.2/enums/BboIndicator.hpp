#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// Indicates the effect the new quote has on the Best Bid and/or the Best Offer.
enum class BboIndicator : char {
    NoBestBidChangeOrBestOfferChange = 'A',           // No Best Bid Change Or Best Offer Change
    NoBestBidChangeQuoteContainsBestOffer = 'B',      // No Best Bid Change Quote Contains Best Offer
    NoBestBidChangeBestOfferAppendage = 'C',          // No Best Bid Change Best Offer Appendage
    NoBestBidChangeNoBestOffer = 'D',                 // No Best Bid Change No Best Offer
    QuoteContainsBestBidNoBestOfferChange = 'E',      // Quote Contains Best Bid No Best Offer Change
    QuoteContainsBestBidQuoteContainsBestOffer = 'F', // Quote Contains Best Bid Quote Contains Best Offer
    QuoteContainsBestBidBestOfferAppendage = 'G',     // Quote Contains Best Bid Best Offer Appendage
    QuoteContainsBestBidNoBestOffer = 'H',            // Quote Contains Best Bid No Best Offer
    NoBestBidNoBestOfferChange = 'I',                 // No Best Bid No Best Offer Change
    NoBestBidQuoteContainsBestOffer = 'J',            // No Best Bid Quote Contains Best Offer
    NoBestBidBestOfferAppendage = 'K',                // No Best Bid Best Offer Appendage
    NoBestBidNoBestOffer = 'L',                       // No Best Bid No Best Offer
    BestBidAppendageNoBestOfferChange = 'M',          // Best Bid Appendage No Best Offer Change
    BestBidAppendageQuoteContainsBestOffer = 'N',     // Best Bid Appendage Quote Contains Best Offer
    BestBidAppendageBestOfferAppendage = 'O',         // Best Bid Appendage Best Offer Appendage
    BestBidAppendageNoBestOffer = 'P',                // Best Bid Appendage No Best Offer
    NotIncludedInTheBbo = ' ',                        // Not Included In The Bbo
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(BboIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, BboIndicator value);

} // namespace siac::opra::output::obi::v6_2
