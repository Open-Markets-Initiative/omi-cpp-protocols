#pragma once

#include "../types/MessageIndicator.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/ExpirationBlock.hpp"
#include "../types/StrikePriceDenominatorCode.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/Volume.hpp"
#include "../types/OpenInterestVolume.hpp"
#include "../types/PremiumPriceDenominatorCode.hpp"
#include "../types/OpenPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/LastPrice.hpp"
#include "../types/NetChange.hpp"
#include "../types/UnderlyingPriceDenominatorCode.hpp"
#include "../types/UnderlyingPrice.hpp"
#include "../types/BidPrice.hpp"
#include "../types/OfferPrice.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

// Equity and Index End of Day Summary Message
struct EquityAndIndexEndOfDaySummaryMessage {

    MessageIndicator message_indicator;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    Reserved1 reserved_1;
    ExpirationBlock expiration_block;
    StrikePriceDenominatorCode strike_price_denominator_code;
    StrikePrice strike_price;
    Volume volume;
    OpenInterestVolume open_interest_volume;
    PremiumPriceDenominatorCode premium_price_denominator_code;
    OpenPrice open_price;
    HighPrice high_price;
    LowPrice low_price;
    LastPrice last_price;
    NetChange net_change;
    UnderlyingPriceDenominatorCode underlying_price_denominator_code;
    UnderlyingPrice underlying_price;
    BidPrice bid_price;
    OfferPrice offer_price;

    // parse method
    static EquityAndIndexEndOfDaySummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EquityAndIndexEndOfDaySummaryMessage*>(buffer);
    }

    // parse method const
    static const EquityAndIndexEndOfDaySummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EquityAndIndexEndOfDaySummaryMessage*>(buffer);
    }
};

#pragma pack(pop)
}
