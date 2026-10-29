#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../structs/CorrectedTrade.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../structs/Timestamp2.hpp"
#include "../types/OriginalParticipantReferenceNumber.hpp"
#include "../structs/OriginalTrade.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../structs/ConsolidatedData.hpp"
#include "../structs/ParticipantData.hpp"

namespace siac::cts::output::cta::v2_9 {

#pragma pack(push, 1)

// The Trade Correction message is used to correct Cta eligible Equity, Local Issue or Bond information.
struct TradeCorrectionMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    InstrumentType instrument_type;
    CorrectedTrade corrected_trade;
    TradeReportingFacilityId trade_reporting_facility_id;
    Timestamp2 timestamp_2;
    OriginalParticipantReferenceNumber original_participant_reference_number;
    OriginalTrade original_trade;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    FinancialStatusIndicator financial_status_indicator;
    ConsolidatedData consolidated_data;
    ParticipantData participant_data;

    // parse method
    static TradeCorrectionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCorrectionMessage*>(buffer);
    }

    // parse method const
    static const TradeCorrectionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCorrectionMessage*>(buffer);
    }
};

#pragma pack(pop)
}
