#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

// Used to signal the end of Start of Day Summary message iterations
struct EndOfStartOfDaySummaryMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;

    // parse method
    static EndOfStartOfDaySummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EndOfStartOfDaySummaryMessage*>(buffer);
    }

    // parse method const
    static const EndOfStartOfDaySummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EndOfStartOfDaySummaryMessage*>(buffer);
    }
};

#pragma pack(pop)
}
