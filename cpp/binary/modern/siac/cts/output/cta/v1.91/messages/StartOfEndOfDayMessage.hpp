#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

// The Start of End of Day message signals the start of Consolidated End of Day Summary and Participant End of Day Summary message iterations
struct StartOfEndOfDayMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;

    // parse method
    static StartOfEndOfDayMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StartOfEndOfDayMessage*>(buffer);
    }

    // parse method const
    static const StartOfEndOfDayMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StartOfEndOfDayMessage*>(buffer);
    }
};

#pragma pack(pop)
}
