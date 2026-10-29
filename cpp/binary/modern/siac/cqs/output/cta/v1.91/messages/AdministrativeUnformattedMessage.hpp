#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/ParticipantTimestamp.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/Text.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

// The Administrative Unformatted (free form text) Category A message is designed to facilitate non-computerized miscellaneous information messages to CQS
struct AdministrativeUnformattedMessage {

    ParticipantId participant_id;
    ParticipantTimestamp participant_timestamp;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    Text text;

    // parse method
    static AdministrativeUnformattedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AdministrativeUnformattedMessage*>(buffer);
    }

    // parse method const
    static const AdministrativeUnformattedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AdministrativeUnformattedMessage*>(buffer);
    }
};

#pragma pack(pop)
}
