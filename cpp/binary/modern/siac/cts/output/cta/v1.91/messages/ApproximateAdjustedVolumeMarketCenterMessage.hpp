#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/NumberOfParticipants.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

// Approximate Adjusted Volume Market Center message is used to report the volume of adjusted trading activity for each Participant.
struct ApproximateAdjustedVolumeMarketCenterMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    NumberOfParticipants number_of_participants;

    // parse method
    static ApproximateAdjustedVolumeMarketCenterMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ApproximateAdjustedVolumeMarketCenterMessage*>(buffer);
    }

    // parse method const
    static const ApproximateAdjustedVolumeMarketCenterMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ApproximateAdjustedVolumeMarketCenterMessage*>(buffer);
    }
};

#pragma pack(pop)
}
