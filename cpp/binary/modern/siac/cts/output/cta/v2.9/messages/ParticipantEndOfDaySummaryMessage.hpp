#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/InitiatingParticipantId.hpp"
#include "../types/PreviousClosePriceDate.hpp"
#include "../types/LastPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/OpenPrice.hpp"
#include "../types/TotalVolume.hpp"
#include "../types/Tick.hpp"

namespace siac::cts::output::cta::v2_9 {

#pragma pack(push, 1)

// The Participant End of Day Summary messages are transmitted shortly before the ‘Goodnight’ messages.
struct ParticipantEndOfDaySummaryMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    InstrumentType instrument_type;
    InitiatingParticipantId initiating_participant_id;
    PreviousClosePriceDate previous_close_price_date;
    LastPrice last_price;
    HighPrice high_price;
    LowPrice low_price;
    OpenPrice open_price;
    TotalVolume total_volume;
    Tick tick;

    // parse method
    static ParticipantEndOfDaySummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ParticipantEndOfDaySummaryMessage*>(buffer);
    }

    // parse method const
    static const ParticipantEndOfDaySummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ParticipantEndOfDaySummaryMessage*>(buffer);
    }
};

#pragma pack(pop)
}
