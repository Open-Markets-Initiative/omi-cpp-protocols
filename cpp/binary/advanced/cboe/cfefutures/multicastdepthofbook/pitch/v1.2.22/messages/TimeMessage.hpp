#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeReference.hpp"
#include "../types/EpochTime.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

namespace pitch_multicastdepthofbook = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

#pragma pack(push, 1)

// Time Message
struct time_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_reference time_reference;
        pitch_multicastdepthofbook::epoch_time epoch_time;
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
static_assert(offsetof(time_message::fields_type, time_reference) == 0, "unexpected offset of time_message::fields_type::time_reference");
static_assert(offsetof(time_message::fields_type, epoch_time) == 4, "unexpected offset of time_message::fields_type::epoch_time");
static_assert(sizeof(time_message::fields_type) == 8, "unexpected sizeof time_message::fields_type");
static_assert(sizeof(time_message) == sizeof(pitch_multicastdepthofbook::message_header) + 8, "unexpected sizeof time_message");

#pragma pack(pop)
}
