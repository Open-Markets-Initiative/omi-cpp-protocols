#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/TerminationCode.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)

// Terminate Message
struct terminate_message {

    struct fields_type {
        sbe_binaryentrypoint::session_id session_id;
        sbe_binaryentrypoint::session_ver_id session_ver_id;
        sbe_binaryentrypoint::termination_code termination_code;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static terminate_message* parse(std::byte* buffer) {
        return reinterpret_cast<terminate_message*>(buffer);
    }

    // parse method const
    static const terminate_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const terminate_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(terminate_message::fields_type, session_id) == 0, "unexpected offset of terminate_message::fields_type::session_id");
static_assert(offsetof(terminate_message::fields_type, session_ver_id) == 4, "unexpected offset of terminate_message::fields_type::session_ver_id");
static_assert(offsetof(terminate_message::fields_type, termination_code) == 12, "unexpected offset of terminate_message::fields_type::termination_code");
static_assert(sizeof(terminate_message::fields_type) == 13, "unexpected sizeof terminate_message::fields_type");
static_assert(sizeof(terminate_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 13, "unexpected sizeof terminate_message");

#pragma pack(pop)
}
