#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/ParticipantTimestamp.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

// The Line Integrity message is transmitted over the multicast lines at intervals of sixty (60) seconds to verify continued integrity of multicast transmission
struct LineIntegrityMessage {

    ParticipantId participant_id;
    ParticipantTimestamp participant_timestamp;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;

    // parse method
    static LineIntegrityMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LineIntegrityMessage*>(buffer);
    }

    // parse method const
    static const LineIntegrityMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LineIntegrityMessage*>(buffer);
    }
};

#pragma pack(pop)
}
