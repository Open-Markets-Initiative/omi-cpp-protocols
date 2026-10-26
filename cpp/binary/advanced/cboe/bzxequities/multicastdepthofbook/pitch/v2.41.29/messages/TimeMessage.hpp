#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Time.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

namespace pitch_multicastdepthofbook = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29;

#pragma pack(push, 1)

// Time Message
struct time_message {

    struct fields_type {
        pitch_multicastdepthofbook::time time;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::time_message};

    fields_type fields;

    // parse method
    static time_message* parse(std::byte* buffer) {
        return reinterpret_cast<time_message*>(buffer);
    }

    // parse method const
    static const time_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const time_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(time_message::fields_type, time) == 0, "unexpected offset of time_message::fields_type::time");
static_assert(sizeof(time_message::fields_type) == 4, "unexpected sizeof time_message::fields_type");
static_assert(sizeof(time_message) == sizeof(pitch_multicastdepthofbook::message_header) + 4, "unexpected sizeof time_message");

#pragma pack(pop)
}
