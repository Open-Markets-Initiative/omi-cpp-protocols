#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/ParticipantTimestamp.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

// The Start of Day message signals the start of normal data dissemination over the multicast lines
struct StartOfDayMessage {

    ParticipantId participant_id;
    ParticipantTimestamp participant_timestamp;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;

    // parse method
    static StartOfDayMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StartOfDayMessage*>(buffer);
    }

    // parse method const
    static const StartOfDayMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StartOfDayMessage*>(buffer);
    }
};

#pragma pack(pop)
}
