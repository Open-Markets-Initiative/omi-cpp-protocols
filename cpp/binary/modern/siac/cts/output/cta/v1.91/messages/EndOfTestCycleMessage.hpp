#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

// The End of Test Cycle message is transmitted to signal the end of the transmission of the repeated free form text test message cycles
struct EndOfTestCycleMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;

    // parse method
    static EndOfTestCycleMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EndOfTestCycleMessage*>(buffer);
    }

    // parse method const
    static const EndOfTestCycleMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EndOfTestCycleMessage*>(buffer);
    }
};

#pragma pack(pop)
}
