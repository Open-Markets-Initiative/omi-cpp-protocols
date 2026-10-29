#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/ControlMessageType.hpp"

namespace siac::cts::output::cta::v2_9 {

namespace cta_output = ::siac::cts::output::cta::v2_9;

#pragma pack(push, 1)

// End Of Day Message
struct end_of_day_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::control;
    cta_output::control_message_type control_message_type = cta_output::control_message_type::enum_type::end_of_day_message;

    fields_type fields;

    // parse method
    static end_of_day_message* parse(std::byte* buffer) {
        return reinterpret_cast<end_of_day_message*>(buffer);
    }

    // parse method const
    static const end_of_day_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const end_of_day_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(end_of_day_message::fields_type, participant_id) == 0, "unexpected offset of end_of_day_message::fields_type::participant_id");
static_assert(offsetof(end_of_day_message::fields_type, timestamp_1) == 1, "unexpected offset of end_of_day_message::fields_type::timestamp_1");
static_assert(offsetof(end_of_day_message::fields_type, message_id) == 9, "unexpected offset of end_of_day_message::fields_type::message_id");
static_assert(offsetof(end_of_day_message::fields_type, transaction_id) == 10, "unexpected offset of end_of_day_message::fields_type::transaction_id");
static_assert(offsetof(end_of_day_message::fields_type, participant_reference_number) == 14, "unexpected offset of end_of_day_message::fields_type::participant_reference_number");
static_assert(sizeof(end_of_day_message::fields_type) == 22, "unexpected sizeof end_of_day_message::fields_type");
static_assert(sizeof(end_of_day_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::control_message_type) + 22, "unexpected sizeof end_of_day_message");

#pragma pack(pop)
}
