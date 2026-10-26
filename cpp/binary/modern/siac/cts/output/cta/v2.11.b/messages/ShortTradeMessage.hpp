#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol5.hpp"
#include "../types/SaleCondition1.hpp"
#include "../types/SaleConditionCategory.hpp"
#include "../types/TradePrice2.hpp"
#include "../types/TradeVolume2.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/ConsolidatedHighLowLastIndicator.hpp"
#include "../types/ParticipantOpenHighLowLastIndicator.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

// Used to report trade information for CTA eligible Equity only. To be descoped when Fractional Trade Volume publication is activated
struct ShortTradeMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol5 security_symbol_5;
    SaleCondition1 sale_condition_1;
    SaleConditionCategory sale_condition_category;
    TradePrice2 trade_price_2;
    TradeVolume2 trade_volume_2;
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
