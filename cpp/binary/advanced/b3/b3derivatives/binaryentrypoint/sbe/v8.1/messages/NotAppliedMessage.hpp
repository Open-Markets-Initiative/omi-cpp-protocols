#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../types/FromSeqNo.hpp"
#include "../types/Count.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;

#pragma pack(push, 1)

// Not Applied Message
struct not_applied_message {

    struct fields_type {
        sbe_binaryentrypoint::from_seq_no from_seq_no;
        sbe_binaryentrypoint::count count;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static not_applied_message* parse(std::byte* buffer) {
        return reinterpret_cast<not_applied_message*>(buffer);
    }

    // parse method const
    static const not_applied_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const not_applied_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(not_applied_message::fields_type, from_seq_no) == 0, "unexpected offset of not_applied_message::fields_type::from_seq_no");
static_assert(offsetof(not_applied_message::fields_type, count) == 4, "unexpected offset of not_applied_message::fields_type::count");
static_assert(sizeof(not_applied_message::fields_type) == 8, "unexpected sizeof not_applied_message::fields_type");
static_assert(sizeof(not_applied_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 8, "unexpected sizeof not_applied_message");

#pragma pack(pop)
}
