#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/LastParticipantId.hpp"
#include "../types/PreviousClosePriceDate.hpp"
#include "../types/LastPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/TotalVolume.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/NumberOfParticipants.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

// Provides by security, the Consolidated High, Low, Last and Volume for CTA eligible Equity, Local Issues and Bonds. To be descoped when Fractional Trade Volume publication is activated
struct ConsolidatedEndOfDaySummaryMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    InstrumentType instrument_type;
    LastParticipantId last_participant_id;
    PreviousClosePriceDate previous_close_price_date;
    LastPrice last_price;
    HighPrice high_price;
    LowPrice low_price;
    TotalVolume total_volume;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    FinancialStatusIndicator financial_status_indicator;
    NumberOfParticipants number_of_participants;

    // parse method
    static ConsolidatedEndOfDaySummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ConsolidatedEndOfDaySummaryMessage*>(buffer);
    }

    // parse method const
    static const ConsolidatedEndOfDaySummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ConsolidatedEndOfDaySummaryMessage*>(buffer);
    }
};

#pragma pack(pop)
}
