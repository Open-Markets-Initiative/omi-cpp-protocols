#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../types/SessionId.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/RetransmitRejectCode.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)

// Retransmit Reject Message
struct retransmit_reject_message {

    struct fields_type {
        sbe_binaryentrypoint::session_id session_id;
        sbe_binaryentrypoint::request_timestamp request_timestamp;
        sbe_binaryentrypoint::retransmit_reject_code retransmit_reject_code;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static retransmit_reject_message* parse(std::byte* buffer) {
        return reinterpret_cast<retransmit_reject_message*>(buffer);
    }

    // parse method const
    static const retransmit_reject_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const retransmit_reject_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(retransmit_reject_message::fields_type, session_id) == 0, "unexpected offset of retransmit_reject_message::fields_type::session_id");
static_assert(offsetof(retransmit_reject_message::fields_type, request_timestamp) == 4, "unexpected offset of retransmit_reject_message::fields_type::request_timestamp");
static_assert(offsetof(retransmit_reject_message::fields_type, retransmit_reject_code) == 12, "unexpected offset of retransmit_reject_message::fields_type::retransmit_reject_code");
static_assert(sizeof(retransmit_reject_message::fields_type) == 13, "unexpected sizeof retransmit_reject_message::fields_type");
static_assert(sizeof(retransmit_reject_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 13, "unexpected sizeof retransmit_reject_message");

#pragma pack(pop)
}
