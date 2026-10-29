#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/ParticipantTimestamp.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

// The FINRA Open message is transmitted by FINRA to CQS
struct FinraOpenMessage {

    ParticipantId participant_id;
    ParticipantTimestamp participant_timestamp;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;

    // parse method
    static FinraOpenMessage* parse(std::byte* buffer) {
        return reinterpret_cast<FinraOpenMessage*>(buffer);
    }

    // parse method const
    static const FinraOpenMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const FinraOpenMessage*>(buffer);
    }
};

#pragma pack(pop)
}
