#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

// Transmitted when the Block Sequence Number on an output multicast line requires resetting
struct ResetBlockSequenceNumberMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;

    // parse method
    static ResetBlockSequenceNumberMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ResetBlockSequenceNumberMessage*>(buffer);
    }

    // parse method const
    static const ResetBlockSequenceNumberMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ResetBlockSequenceNumberMessage*>(buffer);
    }
};

#pragma pack(pop)
}
