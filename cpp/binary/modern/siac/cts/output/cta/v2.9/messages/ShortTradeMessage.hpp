#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbolShort.hpp"
#include "../types/SaleCondition.hpp"
#include "../types/SaleConditionCategory.hpp"
#include "../types/TradePriceShort.hpp"
#include "../types/TradeVolumeShort.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/ConsolidatedHighLowLastIndicator.hpp"
#include "../types/ParticipantOpenHighLowLastIndicator.hpp"

namespace siac::cts::output::cta::v2_9 {

#pragma pack(push, 1)

// The Short Trade message is used to report trade information for Cta eligible Equity only (not used for Local Issues or Bonds) if the trade meets message format requirements otherwise Long Trade message is used.
struct ShortTradeMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbolShort security_symbol_short;
    SaleCondition sale_condition;
    SaleConditionCategory sale_condition_category;
    TradePriceShort trade_price_short;
    TradeVolumeShort trade_volume_short;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator;
    ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator;

    // parse method
    static ShortTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ShortTradeMessage*>(buffer);
    }

    // parse method const
    static const ShortTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ShortTradeMessage*>(buffer);
    }
};

#pragma pack(pop)
}
