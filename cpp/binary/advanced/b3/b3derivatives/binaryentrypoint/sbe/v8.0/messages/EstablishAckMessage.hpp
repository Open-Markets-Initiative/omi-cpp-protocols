#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/KeepAliveInterval.hpp"
#include "../types/NextSeqNo.hpp"
#include "../types/LastIncomingSeqNo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)

// Establish Ack Message
struct establish_ack_message {

    struct fields_type {
        sbe_binaryentrypoint::session_id session_id;
        sbe_binaryentrypoint::session_ver_id session_ver_id;
        sbe_binaryentrypoint::request_timestamp request_timestamp;
        sbe_binaryentrypoint::keep_alive_interval keep_alive_interval;
        sbe_binaryentrypoint::next_seq_no next_seq_no;
        sbe_binaryentrypoint::last_incoming_seq_no last_incoming_seq_no;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static establish_ack_message* parse(std::byte* buffer) {
        return reinterpret_cast<establish_ack_message*>(buffer);
    }

    // parse method const
    static const establish_ack_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const establish_ack_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(establish_ack_message::fields_type, session_id) == 0, "unexpected offset of establish_ack_message::fields_type::session_id");
static_assert(offsetof(establish_ack_message::fields_type, session_ver_id) == 4, "unexpected offset of establish_ack_message::fields_type::session_ver_id");
static_assert(offsetof(establish_ack_message::fields_type, request_timestamp) == 12, "unexpected offset of establish_ack_message::fields_type::request_timestamp");
static_assert(offsetof(establish_ack_message::fields_type, keep_alive_interval) == 20, "unexpected offset of establish_ack_message::fields_type::keep_alive_interval");
static_assert(offsetof(establish_ack_message::fields_type, next_seq_no) == 28, "unexpected offset of establish_ack_message::fields_type::next_seq_no");
static_assert(offsetof(establish_ack_message::fields_type, last_incoming_seq_no) == 32, "unexpected offset of establish_ack_message::fields_type::last_incoming_seq_no");
static_assert(sizeof(establish_ack_message::fields_type) == 36, "unexpected sizeof establish_ack_message::fields_type");
static_assert(sizeof(establish_ack_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 36, "unexpected sizeof establish_ack_message");

#pragma pack(pop)
}
