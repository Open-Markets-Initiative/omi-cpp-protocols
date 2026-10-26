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
#include "../types/LastPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/OpenPrice.hpp"
#include "../types/FractionalTotalVolume.hpp"
#include "../types/Tick.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

// Provides by security, the Participant Open, High, Low, Last, Volume and Tick information for CTA eligible securities, Local Issues and Bonds. Volume is represented as a fractional value
struct FractionalParticipantEndOfDaySummaryMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    InstrumentType instrument_type;
    SummaryParticipantId summary_participant_id;
    PreviousClosePriceDate previous_close_price_date;
    LastPrice last_price;
    HighPrice high_price;
    LowPrice low_price;
    OpenPrice open_price;
    FractionalTotalVolume fractional_total_volume;
    Tick tick;

    // parse method
    static FractionalParticipantEndOfDaySummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<FractionalParticipantEndOfDaySummaryMessage*>(buffer);
    }

    // parse method const
    static const FractionalParticipantEndOfDaySummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const FractionalParticipantEndOfDaySummaryMessage*>(buffer);
    }
};

#pragma pack(pop)
}
