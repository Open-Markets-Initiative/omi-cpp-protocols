#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/ParticipantTimestamp.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/Text.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/AdministrativeMessageType.hpp"

namespace siac::cqs::output::cta::v1_91 {

namespace cta_output = ::siac::cqs::output::cta::v1_91;

#pragma pack(push, 1)

// Administrative Unformatted Message
struct administrative_unformatted_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::participant_timestamp participant_timestamp;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::text text;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::administrative;
    cta_output::administrative_message_type administrative_message_type = cta_output::administrative_message_type::enum_type::administrative_unformatted_message;

    fields_type fields;

    // parse method
    static administrative_unformatted_message* parse(std::byte* buffer) {
        return reinterpret_cast<administrative_unformatted_message*>(buffer);
    }

    // parse method const
    static const administrative_unformatted_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const administrative_unformatted_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(administrative_unformatted_message::fields_type, participant_id) == 0, "unexpected offset of administrative_unformatted_message::fields_type::participant_id");
static_assert(offsetof(administrative_unformatted_message::fields_type, participant_timestamp) == 1, "unexpected offset of administrative_unformatted_message::fields_type::participant_timestamp");
static_assert(offsetof(administrative_unformatted_message::fields_type, message_id) == 9, "unexpected offset of administrative_unformatted_message::fields_type::message_id");
static_assert(offsetof(administrative_unformatted_message::fields_type, transaction_id) == 10, "unexpected offset of administrative_unformatted_message::fields_type::transaction_id");
static_assert(offsetof(administrative_unformatted_message::fields_type, participant_reference_number) == 14, "unexpected offset of administrative_unformatted_message::fields_type::participant_reference_number");
static_assert(offsetof(administrative_unformatted_message::fields_type, text) == 22, "unexpected offset of administrative_unformatted_message::fields_type::text");
static_assert(sizeof(administrative_unformatted_message::fields_type) == 26, "unexpected sizeof administrative_unformatted_message::fields_type");
static_assert(sizeof(administrative_unformatted_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::administrative_message_type) + 26, "unexpected sizeof administrative_unformatted_message");

#pragma pack(pop)
}
