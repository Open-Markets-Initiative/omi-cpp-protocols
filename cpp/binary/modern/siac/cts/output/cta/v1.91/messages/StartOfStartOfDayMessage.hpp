#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

// The Start of Start of Day message signals the end of Consolidated End of Day Summary and Participant End of Day Summary message iterations
struct StartOfStartOfDayMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;

    // parse method
    static StartOfStartOfDayMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StartOfStartOfDayMessage*>(buffer);
    }

    // parse method const
    static const StartOfStartOfDayMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StartOfStartOfDayMessage*>(buffer);
    }
};

#pragma pack(pop)
}
