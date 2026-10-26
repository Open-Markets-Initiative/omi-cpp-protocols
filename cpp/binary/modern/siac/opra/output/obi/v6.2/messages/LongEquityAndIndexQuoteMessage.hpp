#pragma once

#include "../types/BboIndicator.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/ExpirationBlock.hpp"
#include "../types/StrikePriceDenominatorCode.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/PremiumPriceDenominatorCode.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidSize.hpp"
#include "../types/OfferPrice.hpp"
#include "../types/OfferSize.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

// Long Equity and Index Quote Message
struct LongEquityAndIndexQuoteMessage {

    BboIndicator bbo_indicator;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    Reserved1 reserved_1;
    ExpirationBlock expiration_block;
    StrikePriceDenominatorCode strike_price_denominator_code;
    StrikePrice strike_price;
    PremiumPriceDenominatorCode premium_price_denominator_code;
    BidPrice bid_price;
    BidSize bid_size;
    OfferPrice offer_price;
    OfferSize offer_size;

    // parse method
    static LongEquityAndIndexQuoteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LongEquityAndIndexQuoteMessage*>(buffer);
    }

    // parse method const
    static const LongEquityAndIndexQuoteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LongEquityAndIndexQuoteMessage*>(buffer);
    }
};

#pragma pack(pop)
}
