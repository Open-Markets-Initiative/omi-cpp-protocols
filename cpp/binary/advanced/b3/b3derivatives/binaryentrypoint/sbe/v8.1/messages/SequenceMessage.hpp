#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../types/NextSeqNo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;

#pragma pack(push, 1)

// Sequence Message
struct sequence_message {

    struct fields_type {
        sbe_binaryentrypoint::next_seq_no next_seq_no;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static sequence_message* parse(std::byte* buffer) {
        return reinterpret_cast<sequence_message*>(buffer);
    }

    // parse method const
    static const sequence_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const sequence_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(sequence_message::fields_type, next_seq_no) == 0, "unexpected offset of sequence_message::fields_type::next_seq_no");
static_assert(sizeof(sequence_message::fields_type) == 4, "unexpected sizeof sequence_message::fields_type");
static_assert(sizeof(sequence_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 4, "unexpected sizeof sequence_message");

#pragma pack(pop)
}
