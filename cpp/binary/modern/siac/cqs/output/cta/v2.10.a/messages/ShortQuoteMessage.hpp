#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/BidPriceShort.hpp"
#include "../types/BidSizeShort.hpp"
#include "../types/OfferPriceShort.hpp"
#include "../types/OfferSizeShort.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/NationalBboIndicator.hpp"

namespace siac::cqs::output::cta::v2_10_a {

#pragma pack(push, 1)

// Reports Bid and Offer quote information for CTA eligible Equity only if the quote meets all criteria and message format requirements
struct ShortQuoteMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    BidPriceShort bid_price_short;
    BidSizeShort bid_size_short;
    OfferPriceShort offer_price_short;
    OfferSizeShort offer_size_short;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    NationalBboIndicator national_bbo_indicator;

    // parse method
    static ShortQuoteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ShortQuoteMessage*>(buffer);
    }

    // parse method const
    static const ShortQuoteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ShortQuoteMessage*>(buffer);
    }
};

#pragma pack(pop)
}
