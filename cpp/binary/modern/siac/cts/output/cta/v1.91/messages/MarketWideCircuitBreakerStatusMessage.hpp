#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/MarketWideCircuitBreakerLevelIndicator.hpp"
#include "../types/Reserved.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

// The Market-Wide Circuit Breaker Status message is used to report the Market-Wide Circuit Breaker threshold Level that has been breached.
struct MarketWideCircuitBreakerStatusMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    MarketWideCircuitBreakerLevelIndicator market_wide_circuit_breaker_level_indicator;
    Reserved reserved;

    // parse method
    static MarketWideCircuitBreakerStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MarketWideCircuitBreakerStatusMessage*>(buffer);
    }

    // parse method const
    static const MarketWideCircuitBreakerStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketWideCircuitBreakerStatusMessage*>(buffer);
    }
};

#pragma pack(pop)
}
