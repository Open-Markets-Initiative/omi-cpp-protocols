#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/EstablishmentRejectCode.hpp"
#include "../types/Offset21Padding1.hpp"
#include "../types/LastIncomingSeqNoOptional.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)

// Establish Reject Message
struct establish_reject_message {

    struct fields_type {
        sbe_binaryentrypoint::session_id session_id;
        sbe_binaryentrypoint::session_ver_id session_ver_id;
        sbe_binaryentrypoint::request_timestamp request_timestamp;
        sbe_binaryentrypoint::establishment_reject_code establishment_reject_code;
        sbe_binaryentrypoint::offset_21_padding_1 offset_21_padding_1;
        sbe_binaryentrypoint::last_incoming_seq_no_optional last_incoming_seq_no_optional;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static establish_reject_message* parse(std::byte* buffer) {
        return reinterpret_cast<establish_reject_message*>(buffer);
    }

    // parse method const
    static const establish_reject_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const establish_reject_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(establish_reject_message::fields_type, session_id) == 0, "unexpected offset of establish_reject_message::fields_type::session_id");
static_assert(offsetof(establish_reject_message::fields_type, session_ver_id) == 4, "unexpected offset of establish_reject_message::fields_type::session_ver_id");
static_assert(offsetof(establish_reject_message::fields_type, request_timestamp) == 12, "unexpected offset of establish_reject_message::fields_type::request_timestamp");
static_assert(offsetof(establish_reject_message::fields_type, establishment_reject_code) == 20, "unexpected offset of establish_reject_message::fields_type::establishment_reject_code");
static_assert(offsetof(establish_reject_message::fields_type, offset_21_padding_1) == 21, "unexpected offset of establish_reject_message::fields_type::offset_21_padding_1");
static_assert(offsetof(establish_reject_message::fields_type, last_incoming_seq_no_optional) == 22, "unexpected offset of establish_reject_message::fields_type::last_incoming_seq_no_optional");
static_assert(sizeof(establish_reject_message::fields_type) == 26, "unexpected sizeof establish_reject_message::fields_type");
static_assert(sizeof(establish_reject_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 26, "unexpected sizeof establish_reject_message");

#pragma pack(pop)
}
