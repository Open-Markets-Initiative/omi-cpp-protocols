#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/ParticipantTimestamp.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

// The FINRA Close message is transmitted by FINRA to CQS to indicate the Close state of FINRA Market Maker(s).
struct FinraCloseMessage {

    ParticipantId participant_id;
    ParticipantTimestamp participant_timestamp;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;

    // parse method
    static FinraCloseMessage* parse(std::byte* buffer) {
        return reinterpret_cast<FinraCloseMessage*>(buffer);
    }

    // parse method const
    static const FinraCloseMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const FinraCloseMessage*>(buffer);
    }
};

#pragma pack(pop)
}
