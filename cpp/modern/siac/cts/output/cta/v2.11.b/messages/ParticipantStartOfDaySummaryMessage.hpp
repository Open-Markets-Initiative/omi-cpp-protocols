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

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

// Provides, by security, Participant previous close price and previous close price date information for CTA eligible Equity, Local Issues and Bonds
struct ParticipantStartOfDaySummaryMessage {

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

    // parse method
    static ParticipantStartOfDaySummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ParticipantStartOfDaySummaryMessage*>(buffer);
    }

    // parse method const
    static const ParticipantStartOfDaySummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ParticipantStartOfDaySummaryMessage*>(buffer);
    }
};

#pragma pack(pop)
}
