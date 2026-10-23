#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

// Used to signal the start of Consolidated End of Day Summary and Participant End of Day Summary message iterations
struct StartOfEndOfDaySummaryMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;

    // parse method
    static StartOfEndOfDaySummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StartOfEndOfDaySummaryMessage*>(buffer);
    }

    // parse method const
    static const StartOfEndOfDaySummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StartOfEndOfDaySummaryMessage*>(buffer);
    }
};

#pragma pack(pop)
}
