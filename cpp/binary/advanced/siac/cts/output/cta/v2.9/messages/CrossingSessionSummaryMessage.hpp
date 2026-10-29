#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/CrossingSessionITotalTradesVolume.hpp"
#include "../types/CrossingSessionIiDollarValue.hpp"
#include "../types/CrossingSessionIiTotalTradesVolume.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/MarketStatusMessageType.hpp"

namespace siac::cts::output::cta::v2_9 {

namespace cta_output = ::siac::cts::output::cta::v2_9;

#pragma pack(push, 1)

// Crossing Session Summary Message
struct crossing_session_summary_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::crossing_session_i_total_trades_volume crossing_session_i_total_trades_volume;
        cta_output::crossing_session_ii_dollar_value crossing_session_ii_dollar_value;
        cta_output::crossing_session_ii_total_trades_volume crossing_session_ii_total_trades_volume;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::market_status;
    cta_output::market_status_message_type market_status_message_type = cta_output::market_status_message_type::enum_type::crossing_session_summary_message;

    fields_type fields;

    // parse method
    static crossing_session_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<crossing_session_summary_message*>(buffer);
    }

    // parse method const
    static const crossing_session_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const crossing_session_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(crossing_session_summary_message::fields_type, participant_id) == 0, "unexpected offset of crossing_session_summary_message::fields_type::participant_id");
static_assert(offsetof(crossing_session_summary_message::fields_type, timestamp_1) == 1, "unexpected offset of crossing_session_summary_message::fields_type::timestamp_1");
static_assert(offsetof(crossing_session_summary_message::fields_type, message_id) == 9, "unexpected offset of crossing_session_summary_message::fields_type::message_id");
static_assert(offsetof(crossing_session_summary_message::fields_type, transaction_id) == 10, "unexpected offset of crossing_session_summary_message::fields_type::transaction_id");
static_assert(offsetof(crossing_session_summary_message::fields_type, participant_reference_number) == 14, "unexpected offset of crossing_session_summary_message::fields_type::participant_reference_number");
static_assert(offsetof(crossing_session_summary_message::fields_type, crossing_session_i_total_trades_volume) == 22, "unexpected offset of crossing_session_summary_message::fields_type::crossing_session_i_total_trades_volume");
static_assert(offsetof(crossing_session_summary_message::fields_type, crossing_session_ii_dollar_value) == 30, "unexpected offset of crossing_session_summary_message::fields_type::crossing_session_ii_dollar_value");
static_assert(offsetof(crossing_session_summary_message::fields_type, crossing_session_ii_total_trades_volume) == 38, "unexpected offset of crossing_session_summary_message::fields_type::crossing_session_ii_total_trades_volume");
static_assert(sizeof(crossing_session_summary_message::fields_type) == 46, "unexpected sizeof crossing_session_summary_message::fields_type");
static_assert(sizeof(crossing_session_summary_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::market_status_message_type) + 46, "unexpected sizeof crossing_session_summary_message");

#pragma pack(pop)
}
