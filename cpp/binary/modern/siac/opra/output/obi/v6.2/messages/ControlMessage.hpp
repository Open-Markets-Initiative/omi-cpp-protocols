#pragma once

#include "../types/MessageIndicator.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

// Control Message
struct ControlMessage {

    MessageIndicator message_indicator;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;

    // parse method
    static ControlMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ControlMessage*>(buffer);
    }

    // parse method const
    static const ControlMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ControlMessage*>(buffer);
    }
};

#pragma pack(pop)
}
