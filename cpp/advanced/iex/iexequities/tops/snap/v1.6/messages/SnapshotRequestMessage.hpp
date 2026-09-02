#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/AuthenticationToken.hpp"
#include "../types/ChannelId.hpp"
#include "../types/SessionId.hpp"
#include "../types/MinimumSequenceNumber.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

namespace snap_tops = ::iex::iexequities::tops::snap::v1_6;

#pragma pack(push, 1)

// Snapshot Request Message
struct snapshot_request_message {

    struct fields_type {
        snap_tops::authentication_token authentication_token;
        snap_tops::channel_id channel_id;
        snap_tops::session_id session_id;
        snap_tops::minimum_sequence_number minimum_sequence_number;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::snapshot_request_message};

    fields_type fields;

    // parse method
    static snapshot_request_message* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_request_message*>(buffer);
    }

    // parse method const
    static const snapshot_request_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_request_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(snapshot_request_message::fields_type, authentication_token) == 0, "unexpected offset of snapshot_request_message::fields_type::authentication_token");
static_assert(offsetof(snapshot_request_message::fields_type, channel_id) == 40, "unexpected offset of snapshot_request_message::fields_type::channel_id");
static_assert(offsetof(snapshot_request_message::fields_type, session_id) == 44, "unexpected offset of snapshot_request_message::fields_type::session_id");
static_assert(offsetof(snapshot_request_message::fields_type, minimum_sequence_number) == 48, "unexpected offset of snapshot_request_message::fields_type::minimum_sequence_number");
static_assert(sizeof(snapshot_request_message::fields_type) == 56, "unexpected sizeof snapshot_request_message::fields_type");
static_assert(sizeof(snapshot_request_message) == sizeof(message_header) + 56, "unexpected sizeof snapshot_request_message");

#pragma pack(pop)
}
