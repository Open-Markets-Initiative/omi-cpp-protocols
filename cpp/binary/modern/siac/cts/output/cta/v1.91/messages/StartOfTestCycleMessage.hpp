#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

// The Start of Test Cycle message is transmitted to signal the beginning of the transmission of test message cycles
struct StartOfTestCycleMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;

    // parse method
    static StartOfTestCycleMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StartOfTestCycleMessage*>(buffer);
    }

    // parse method const
    static const StartOfTestCycleMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StartOfTestCycleMessage*>(buffer);
    }
};

#pragma pack(pop)
}
