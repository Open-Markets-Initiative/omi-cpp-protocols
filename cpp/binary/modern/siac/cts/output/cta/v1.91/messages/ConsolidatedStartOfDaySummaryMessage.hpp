#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/SummaryParticipantId.hpp"
#include "../types/PreviousClosePriceDate.hpp"
#include "../types/PreviousClosePrice.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/NumberOfParticipants.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

// The Consolidated Start of Day Summary messages are transmitted shortly after the Multicast Line ‘Start of Day’ message
struct ConsolidatedStartOfDaySummaryMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    InstrumentType instrument_type;
    SummaryParticipantId summary_participant_id;
    PreviousClosePriceDate previous_close_price_date;
    PreviousClosePrice previous_close_price;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    FinancialStatusIndicator financial_status_indicator;
    NumberOfParticipants number_of_participants;

    // parse method
    static ConsolidatedStartOfDaySummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ConsolidatedStartOfDaySummaryMessage*>(buffer);
    }

    // parse method const
    static const ConsolidatedStartOfDaySummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ConsolidatedStartOfDaySummaryMessage*>(buffer);
    }
};

#pragma pack(pop)
}
