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
#include "../structs/OriginalTrade.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

// The Prior Day Correction message is used to correct a transaction originally reported on a trading day earlier than the current trading day
struct PriorDayTradeCorrectionMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    InstrumentType instrument_type;
    CorrectedTrade corrected_trade;
    TradeReportingFacilityId trade_reporting_facility_id;
    OriginalTrade original_trade;

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
