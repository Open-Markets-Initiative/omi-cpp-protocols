#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/RejectReasonCode.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

namespace snap_tops = ::iex::iexequities::tops::snap::v1_6;

#pragma pack(push, 1)

// Error Response Message
struct error_response_message {

    struct fields_type {
        snap_tops::reject_reason_code reject_reason_code;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::error_response_message};

    fields_type fields;

    // parse method
    static error_response_message* parse(std::byte* buffer) {
        return reinterpret_cast<error_response_message*>(buffer);
    }

    // parse method const
    static const error_response_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const error_response_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(error_response_message::fields_type, reject_reason_code) == 0, "unexpected offset of error_response_message::fields_type::reject_reason_code");
static_assert(sizeof(error_response_message::fields_type) == 1, "unexpected sizeof error_response_message::fields_type");
static_assert(sizeof(error_response_message) == sizeof(message_header) + 1, "unexpected sizeof error_response_message");

#pragma pack(pop)
}
