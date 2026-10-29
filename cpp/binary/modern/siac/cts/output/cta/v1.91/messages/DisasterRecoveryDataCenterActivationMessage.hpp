#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

// The Disaster Recovery Data Center Activation message is transmitted to signify that the Consolidated Quotation System (CQS) has switched processing from the Primary Data Center to the Disaster Recovery Data Center
struct DisasterRecoveryDataCenterActivationMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;

    // parse method
    static DisasterRecoveryDataCenterActivationMessage* parse(std::byte* buffer) {
        return reinterpret_cast<DisasterRecoveryDataCenterActivationMessage*>(buffer);
    }

    // parse method const
    static const DisasterRecoveryDataCenterActivationMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const DisasterRecoveryDataCenterActivationMessage*>(buffer);
    }
};

#pragma pack(pop)
}
