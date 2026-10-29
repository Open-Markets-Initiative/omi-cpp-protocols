#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/EnteringFirm.hpp"
#include "../structs/SemanticVersion.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;

#pragma pack(push, 1)

// Negotiate Response Message
struct negotiate_response_message {

    struct fields_type {
        sbe_binaryentrypoint::session_id session_id;
        sbe_binaryentrypoint::session_ver_id session_ver_id;
        sbe_binaryentrypoint::request_timestamp request_timestamp;
        sbe_binaryentrypoint::entering_firm entering_firm;
        sbe_binaryentrypoint::semantic_version semantic_version;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static negotiate_response_message* parse(std::byte* buffer) {
        return reinterpret_cast<negotiate_response_message*>(buffer);
    }

    // parse method const
    static const negotiate_response_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const negotiate_response_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(negotiate_response_message::fields_type, session_id) == 0, "unexpected offset of negotiate_response_message::fields_type::session_id");
static_assert(offsetof(negotiate_response_message::fields_type, session_ver_id) == 4, "unexpected offset of negotiate_response_message::fields_type::session_ver_id");
static_assert(offsetof(negotiate_response_message::fields_type, request_timestamp) == 12, "unexpected offset of negotiate_response_message::fields_type::request_timestamp");
static_assert(offsetof(negotiate_response_message::fields_type, entering_firm) == 20, "unexpected offset of negotiate_response_message::fields_type::entering_firm");
static_assert(offsetof(negotiate_response_message::fields_type, semantic_version) == 24, "unexpected offset of negotiate_response_message::fields_type::semantic_version");
static_assert(sizeof(negotiate_response_message::fields_type) == 28, "unexpected sizeof negotiate_response_message::fields_type");
static_assert(sizeof(negotiate_response_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 28, "unexpected sizeof negotiate_response_message");

#pragma pack(pop)
}
