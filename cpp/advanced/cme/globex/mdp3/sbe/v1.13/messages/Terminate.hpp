#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Reason.hpp"
#include "../types/Uuid.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/ErrorCodes.hpp"
#include "../types/Padding5.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

// Terminate
struct terminate {

    struct fields_type {
        sbe_mdp3::reason reason;
        sbe_mdp3::uuid uuid;
        sbe_mdp3::request_timestamp request_timestamp;
        sbe_mdp3::error_codes error_codes;
        sbe_mdp3::padding_5 padding_5;
    };

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, template_id::enum_type::terminate, schema_id::enum_type::mdpsessionmgmt, version(13)};

    fields_type fields;

    // parse method
    static terminate* parse(std::byte* buffer) {
        return reinterpret_cast<terminate*>(buffer);
    }

    // parse method const
    static const terminate* parse(const std::byte* buffer) {
        return reinterpret_cast<const terminate*>(buffer);
    }

};

// layout verification
static_assert(offsetof(terminate::fields_type, reason) == 0, "unexpected offset of terminate::fields_type::reason");
static_assert(offsetof(terminate::fields_type, uuid) == 48, "unexpected offset of terminate::fields_type::uuid");
static_assert(offsetof(terminate::fields_type, request_timestamp) == 56, "unexpected offset of terminate::fields_type::request_timestamp");
static_assert(offsetof(terminate::fields_type, error_codes) == 64, "unexpected offset of terminate::fields_type::error_codes");
static_assert(offsetof(terminate::fields_type, padding_5) == 65, "unexpected offset of terminate::fields_type::padding_5");
static_assert(sizeof(terminate::fields_type) == 70, "unexpected sizeof terminate::fields_type");
static_assert(sizeof(terminate) == sizeof(sbe_mdp3::message_size) + sizeof(sbe_mdp3::message_header) + 70, "unexpected sizeof terminate");

#pragma pack(pop)
}
