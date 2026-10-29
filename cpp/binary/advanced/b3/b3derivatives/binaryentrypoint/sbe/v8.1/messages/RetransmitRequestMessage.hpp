#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../types/SessionId.hpp"
#include "../types/Timestamp.hpp"
#include "../types/FromSeqNo.hpp"
#include "../types/Count.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;

#pragma pack(push, 1)

// Retransmit Request Message
struct retransmit_request_message {

    struct fields_type {
        sbe_binaryentrypoint::session_id session_id;
        sbe_binaryentrypoint::timestamp timestamp;
        sbe_binaryentrypoint::from_seq_no from_seq_no;
        sbe_binaryentrypoint::count count;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static retransmit_request_message* parse(std::byte* buffer) {
        return reinterpret_cast<retransmit_request_message*>(buffer);
    }

    // parse method const
    static const retransmit_request_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const retransmit_request_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(retransmit_request_message::fields_type, session_id) == 0, "unexpected offset of retransmit_request_message::fields_type::session_id");
static_assert(offsetof(retransmit_request_message::fields_type, timestamp) == 4, "unexpected offset of retransmit_request_message::fields_type::timestamp");
static_assert(offsetof(retransmit_request_message::fields_type, from_seq_no) == 12, "unexpected offset of retransmit_request_message::fields_type::from_seq_no");
static_assert(offsetof(retransmit_request_message::fields_type, count) == 16, "unexpected offset of retransmit_request_message::fields_type::count");
static_assert(sizeof(retransmit_request_message::fields_type) == 20, "unexpected sizeof retransmit_request_message::fields_type");
static_assert(sizeof(retransmit_request_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 20, "unexpected sizeof retransmit_request_message");

#pragma pack(pop)
}
