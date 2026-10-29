#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../structs/FractionalCorrectedTrade.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../structs/Timestamp2.hpp"
#include "../types/OriginalParticipantReferenceNumber.hpp"
#include "../structs/FractionalOriginalTrade.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../structs/FractionalConsolidatedData.hpp"
#include "../structs/FractionalParticipantData.hpp"

namespace siac::cts::output::cta::v2_10 {

#pragma pack(push, 1)

// The Trade Correction message is used to correct Cta eligible Equity, Local Issue or Bond information.
struct FractionalTradeCorrectionMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    InstrumentType instrument_type;
    FractionalCorrectedTrade fractional_corrected_trade;
    TradeReportingFacilityId trade_reporting_facility_id;
    Timestamp2 timestamp_2;
    OriginalParticipantReferenceNumber original_participant_reference_number;
    FractionalOriginalTrade fractional_original_trade;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    FinancialStatusIndicator financial_status_indicator;
    FractionalConsolidatedData fractional_consolidated_data;
    FractionalParticipantData fractional_participant_data;

    // parse method
    static FractionalTradeCorrectionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<FractionalTradeCorrectionMessage*>(buffer);
    }

    // parse method const
    static const FractionalTradeCorrectionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const FractionalTradeCorrectionMessage*>(buffer);
    }
};

#pragma pack(pop)
}
