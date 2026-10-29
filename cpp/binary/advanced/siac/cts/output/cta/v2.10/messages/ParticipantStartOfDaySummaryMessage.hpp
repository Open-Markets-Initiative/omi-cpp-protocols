#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/SummaryParticipantId.hpp"
#include "../types/PreviousClosePriceDate.hpp"
#include "../types/PreviousClosePrice.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/SummaryMessageType.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

#pragma pack(push, 1)

// Participant Start Of Day Summary Message
struct participant_start_of_day_summary_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol security_symbol;
        cta_output::instrument_type instrument_type;
        cta_output::summary_participant_id summary_participant_id;
        cta_output::previous_close_price_date previous_close_price_date;
        cta_output::previous_close_price previous_close_price;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::summary;
    cta_output::summary_message_type summary_message_type = cta_output::summary_message_type::enum_type::participant_start_of_day_summary_message;

    fields_type fields;

    // parse method
    static participant_start_of_day_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<participant_start_of_day_summary_message*>(buffer);
    }

    // parse method const
    static const participant_start_of_day_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const participant_start_of_day_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(participant_start_of_day_summary_message::fields_type, participant_id) == 0, "unexpected offset of participant_start_of_day_summary_message::fields_type::participant_id");
static_assert(offsetof(participant_start_of_day_summary_message::fields_type, timestamp_1) == 1, "unexpected offset of participant_start_of_day_summary_message::fields_type::timestamp_1");
static_assert(offsetof(participant_start_of_day_summary_message::fields_type, message_id) == 9, "unexpected offset of participant_start_of_day_summary_message::fields_type::message_id");
static_assert(offsetof(participant_start_of_day_summary_message::fields_type, transaction_id) == 10, "unexpected offset of participant_start_of_day_summary_message::fields_type::transaction_id");
static_assert(offsetof(participant_start_of_day_summary_message::fields_type, participant_reference_number) == 14, "unexpected offset of participant_start_of_day_summary_message::fields_type::participant_reference_number");
static_assert(offsetof(participant_start_of_day_summary_message::fields_type, security_symbol) == 22, "unexpected offset of participant_start_of_day_summary_message::fields_type::security_symbol");
static_assert(offsetof(participant_start_of_day_summary_message::fields_type, instrument_type) == 33, "unexpected offset of participant_start_of_day_summary_message::fields_type::instrument_type");
static_assert(offsetof(participant_start_of_day_summary_message::fields_type, summary_participant_id) == 34, "unexpected offset of participant_start_of_day_summary_message::fields_type::summary_participant_id");
static_assert(offsetof(participant_start_of_day_summary_message::fields_type, previous_close_price_date) == 35, "unexpected offset of participant_start_of_day_summary_message::fields_type::previous_close_price_date");
static_assert(offsetof(participant_start_of_day_summary_message::fields_type, previous_close_price) == 39, "unexpected offset of participant_start_of_day_summary_message::fields_type::previous_close_price");
static_assert(sizeof(participant_start_of_day_summary_message::fields_type) == 47, "unexpected sizeof participant_start_of_day_summary_message::fields_type");
static_assert(sizeof(participant_start_of_day_summary_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::summary_message_type) + 47, "unexpected sizeof participant_start_of_day_summary_message");

#pragma pack(pop)
}
