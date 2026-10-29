#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../structs/PriorDayCorrectedTrade.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../structs/PriorDayOriginalTrade.hpp"

namespace siac::cts::output::cta::v2_10 {

#pragma pack(push, 1)

// Prior Day messages are used to report CTA eligible Equity, Local Issue or Bond trades, corrections, cancels or errors for transactions that occurred earlier than the current trading day and had not been reported
struct PriorDayTradeCorrectionMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    InstrumentType instrument_type;
    PriorDayCorrectedTrade prior_day_corrected_trade;
    TradeReportingFacilityId trade_reporting_facility_id;
    PriorDayOriginalTrade prior_day_original_trade;

    // parse method
    static PriorDayTradeCorrectionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<PriorDayTradeCorrectionMessage*>(buffer);
    }

    // parse method const
    static const PriorDayTradeCorrectionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const PriorDayTradeCorrectionMessage*>(buffer);
    }
};

#pragma pack(pop)
}
