#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/EnteringFirmOptional.hpp"
#include "../types/NegotiationRejectCode.hpp"
#include "../types/Offset25Padding3.hpp"
#include "../types/CurrentSessionVerId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;

#pragma pack(push, 1)

// Negotiate Reject Message
struct negotiate_reject_message {

    struct fields_type {
        sbe_binaryentrypoint::session_id session_id;
        sbe_binaryentrypoint::session_ver_id session_ver_id;
        sbe_binaryentrypoint::request_timestamp request_timestamp;
        sbe_binaryentrypoint::entering_firm_optional entering_firm_optional;
        sbe_binaryentrypoint::negotiation_reject_code negotiation_reject_code;
        sbe_binaryentrypoint::offset_25_padding_3 offset_25_padding_3;
        sbe_binaryentrypoint::current_session_ver_id current_session_ver_id;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static negotiate_reject_message* parse(std::byte* buffer) {
        return reinterpret_cast<negotiate_reject_message*>(buffer);
    }

    // parse method const
    static const negotiate_reject_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const negotiate_reject_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(negotiate_reject_message::fields_type, session_id) == 0, "unexpected offset of negotiate_reject_message::fields_type::session_id");
static_assert(offsetof(negotiate_reject_message::fields_type, session_ver_id) == 4, "unexpected offset of negotiate_reject_message::fields_type::session_ver_id");
static_assert(offsetof(negotiate_reject_message::fields_type, request_timestamp) == 12, "unexpected offset of negotiate_reject_message::fields_type::request_timestamp");
static_assert(offsetof(negotiate_reject_message::fields_type, entering_firm_optional) == 20, "unexpected offset of negotiate_reject_message::fields_type::entering_firm_optional");
static_assert(offsetof(negotiate_reject_message::fields_type, negotiation_reject_code) == 24, "unexpected offset of negotiate_reject_message::fields_type::negotiation_reject_code");
static_assert(offsetof(negotiate_reject_message::fields_type, offset_25_padding_3) == 25, "unexpected offset of negotiate_reject_message::fields_type::offset_25_padding_3");
static_assert(offsetof(negotiate_reject_message::fields_type, current_session_ver_id) == 28, "unexpected offset of negotiate_reject_message::fields_type::current_session_ver_id");
static_assert(sizeof(negotiate_reject_message::fields_type) == 36, "unexpected sizeof negotiate_reject_message::fields_type");
static_assert(sizeof(negotiate_reject_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 36, "unexpected sizeof negotiate_reject_message");

#pragma pack(pop)
}
