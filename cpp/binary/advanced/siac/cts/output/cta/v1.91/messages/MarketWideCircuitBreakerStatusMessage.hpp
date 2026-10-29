#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/MarketWideCircuitBreakerLevelIndicator.hpp"
#include "../types/Reserved.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/MarketStatusMessageType.hpp"

namespace siac::cts::output::cta::v1_91 {

namespace cta_output = ::siac::cts::output::cta::v1_91;

#pragma pack(push, 1)

// Market Wide Circuit Breaker Status Message
struct market_wide_circuit_breaker_status_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::market_wide_circuit_breaker_level_indicator market_wide_circuit_breaker_level_indicator;
        cta_output::reserved reserved;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::market_status;
    cta_output::market_status_message_type market_status_message_type = cta_output::market_status_message_type::enum_type::market_wide_circuit_breaker_status_message;

    fields_type fields;

    // parse method
    static market_wide_circuit_breaker_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<market_wide_circuit_breaker_status_message*>(buffer);
    }

    // parse method const
    static const market_wide_circuit_breaker_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const market_wide_circuit_breaker_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(market_wide_circuit_breaker_status_message::fields_type, participant_id) == 0, "unexpected offset of market_wide_circuit_breaker_status_message::fields_type::participant_id");
static_assert(offsetof(market_wide_circuit_breaker_status_message::fields_type, timestamp_1) == 1, "unexpected offset of market_wide_circuit_breaker_status_message::fields_type::timestamp_1");
static_assert(offsetof(market_wide_circuit_breaker_status_message::fields_type, message_id) == 9, "unexpected offset of market_wide_circuit_breaker_status_message::fields_type::message_id");
static_assert(offsetof(market_wide_circuit_breaker_status_message::fields_type, transaction_id) == 10, "unexpected offset of market_wide_circuit_breaker_status_message::fields_type::transaction_id");
static_assert(offsetof(market_wide_circuit_breaker_status_message::fields_type, participant_reference_number) == 14, "unexpected offset of market_wide_circuit_breaker_status_message::fields_type::participant_reference_number");
static_assert(offsetof(market_wide_circuit_breaker_status_message::fields_type, market_wide_circuit_breaker_level_indicator) == 22, "unexpected offset of market_wide_circuit_breaker_status_message::fields_type::market_wide_circuit_breaker_level_indicator");
static_assert(offsetof(market_wide_circuit_breaker_status_message::fields_type, reserved) == 23, "unexpected offset of market_wide_circuit_breaker_status_message::fields_type::reserved");
static_assert(sizeof(market_wide_circuit_breaker_status_message::fields_type) == 24, "unexpected sizeof market_wide_circuit_breaker_status_message::fields_type");
static_assert(sizeof(market_wide_circuit_breaker_status_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::market_status_message_type) + 24, "unexpected sizeof market_wide_circuit_breaker_status_message");

#pragma pack(pop)
}
