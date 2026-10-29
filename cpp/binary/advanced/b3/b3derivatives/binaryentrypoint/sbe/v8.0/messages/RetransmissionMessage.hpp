#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../types/SessionId.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/NextSeqNo.hpp"
#include "../types/Count.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)

// Retransmission Message
struct retransmission_message {

    struct fields_type {
        sbe_binaryentrypoint::session_id session_id;
        sbe_binaryentrypoint::request_timestamp request_timestamp;
        sbe_binaryentrypoint::next_seq_no next_seq_no;
        sbe_binaryentrypoint::count count;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static retransmission_message* parse(std::byte* buffer) {
        return reinterpret_cast<retransmission_message*>(buffer);
    }

    // parse method const
    static const retransmission_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const retransmission_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(retransmission_message::fields_type, session_id) == 0, "unexpected offset of retransmission_message::fields_type::session_id");
static_assert(offsetof(retransmission_message::fields_type, request_timestamp) == 4, "unexpected offset of retransmission_message::fields_type::request_timestamp");
static_assert(offsetof(retransmission_message::fields_type, next_seq_no) == 12, "unexpected offset of retransmission_message::fields_type::next_seq_no");
static_assert(offsetof(retransmission_message::fields_type, count) == 16, "unexpected offset of retransmission_message::fields_type::count");
static_assert(sizeof(retransmission_message::fields_type) == 20, "unexpected sizeof retransmission_message::fields_type");
static_assert(sizeof(retransmission_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 20, "unexpected sizeof retransmission_message");

#pragma pack(pop)
}
