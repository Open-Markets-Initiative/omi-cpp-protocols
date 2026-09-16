#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeSeconds.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

// Seconds Timestamp Message
struct seconds_timestamp_message {

    struct fields_type {
        flex_marketbyorder::time_seconds time_seconds;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 1), message_type::enum_type::seconds_timestamp_message};

    fields_type fields;

    // parse method
    static seconds_timestamp_message* parse(std::byte* buffer) {
        return reinterpret_cast<seconds_timestamp_message*>(buffer);
    }

    // parse method const
    static const seconds_timestamp_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const seconds_timestamp_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(seconds_timestamp_message::fields_type, time_seconds) == 0, "unexpected offset of seconds_timestamp_message::fields_type::time_seconds");
static_assert(sizeof(seconds_timestamp_message::fields_type) == 4, "unexpected sizeof seconds_timestamp_message::fields_type");
static_assert(sizeof(seconds_timestamp_message) == sizeof(message_header) + 4, "unexpected sizeof seconds_timestamp_message");

#pragma pack(pop)
}
