#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/TotalTrades.hpp"
#include "../types/DollarValue.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/MarketStatusMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

namespace cta_output = ::siac::cts::output::cta::v2_11_b;

#pragma pack(push, 1)

// Approximate Trades And Total Dollar Value Message
struct approximate_trades_and_total_dollar_value_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::total_trades total_trades;
        cta_output::dollar_value dollar_value;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::market_status;
    cta_output::market_status_message_type market_status_message_type = cta_output::market_status_message_type::enum_type::approximate_trades_and_total_dollar_value;

    fields_type fields;

    // parse method
    static approximate_trades_and_total_dollar_value_message* parse(std::byte* buffer) {
        return reinterpret_cast<approximate_trades_and_total_dollar_value_message*>(buffer);
    }

    // parse method const
    static const approximate_trades_and_total_dollar_value_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const approximate_trades_and_total_dollar_value_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(approximate_trades_and_total_dollar_value_message::fields_type, participant_id) == 0, "unexpected offset of approximate_trades_and_total_dollar_value_message::fields_type::participant_id");
static_assert(offsetof(approximate_trades_and_total_dollar_value_message::fields_type, timestamp_1) == 1, "unexpected offset of approximate_trades_and_total_dollar_value_message::fields_type::timestamp_1");
static_assert(offsetof(approximate_trades_and_total_dollar_value_message::fields_type, message_id) == 9, "unexpected offset of approximate_trades_and_total_dollar_value_message::fields_type::message_id");
static_assert(offsetof(approximate_trades_and_total_dollar_value_message::fields_type, transaction_id) == 10, "unexpected offset of approximate_trades_and_total_dollar_value_message::fields_type::transaction_id");
static_assert(offsetof(approximate_trades_and_total_dollar_value_message::fields_type, participant_reference_number) == 14, "unexpected offset of approximate_trades_and_total_dollar_value_message::fields_type::participant_reference_number");
static_assert(offsetof(approximate_trades_and_total_dollar_value_message::fields_type, total_trades) == 22, "unexpected offset of approximate_trades_and_total_dollar_value_message::fields_type::total_trades");
static_assert(offsetof(approximate_trades_and_total_dollar_value_message::fields_type, dollar_value) == 26, "unexpected offset of approximate_trades_and_total_dollar_value_message::fields_type::dollar_value");
static_assert(sizeof(approximate_trades_and_total_dollar_value_message::fields_type) == 34, "unexpected sizeof approximate_trades_and_total_dollar_value_message::fields_type");
static_assert(sizeof(approximate_trades_and_total_dollar_value_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::market_status_message_type) + 34, "unexpected sizeof approximate_trades_and_total_dollar_value_message");

#pragma pack(pop)
}
