#pragma once

#include "../types/BboIndicator.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbolShort.hpp"
#include "../structs/ExpirationBlock.hpp"
#include "../types/StrikePriceShort.hpp"
#include "../types/BidPriceShort.hpp"
#include "../types/BidSizeShort.hpp"
#include "../types/OfferPriceShort.hpp"
#include "../types/OfferSizeShort.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

// Short Equity and Index Quote Message
struct ShortEquityAndIndexQuoteMessage {

    BboIndicator bbo_indicator;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbolShort security_symbol_short;
    ExpirationBlock expiration_block;
    StrikePriceShort strike_price_short;
    BidPriceShort bid_price_short;
    BidSizeShort bid_size_short;
    OfferPriceShort offer_price_short;
    OfferSizeShort offer_size_short;

    // parse method
    static ShortEquityAndIndexQuoteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ShortEquityAndIndexQuoteMessage*>(buffer);
    }

    // parse method const
    static const ShortEquityAndIndexQuoteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ShortEquityAndIndexQuoteMessage*>(buffer);
    }
};

#pragma pack(pop)
}
