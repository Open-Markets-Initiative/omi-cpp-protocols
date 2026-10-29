#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/MwcbLevel1.hpp"
#include "../types/MwcbLevel2.hpp"
#include "../types/MwcbLevel3.hpp"
#include "../types/Reserved.hpp"

namespace siac::cts::output::cta::v2_10 {

#pragma pack(push, 1)

// The Market-Wide Circuit Breaker Decline Level Status message is used to report the calculated Level 1, Level 2 and Level 3 threshold values for the current trading day necessary to trigger a circuit breaker
struct MarketWideCircuitBreakerDeclineLevelStatusMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    MwcbLevel1 mwcb_level_1;
    MwcbLevel2 mwcb_level_2;
    MwcbLevel3 mwcb_level_3;
    Reserved reserved;

    // parse method
    static MarketWideCircuitBreakerDeclineLevelStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MarketWideCircuitBreakerDeclineLevelStatusMessage*>(buffer);
    }

    // parse method const
    static const MarketWideCircuitBreakerDeclineLevelStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketWideCircuitBreakerDeclineLevelStatusMessage*>(buffer);
    }
};

#pragma pack(pop)
}
