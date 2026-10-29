#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

namespace pitch_multicastdepthofbook = ::cboe::c1options::multicastdepthofbook::pitch::v2_39_4;

#pragma pack(push, 1)

// End Of Session Message
struct end_of_session_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::end_of_session_message};

    fields_type fields;

    // parse method
    static end_of_session_message* parse(std::byte* buffer) {
        return reinterpret_cast<end_of_session_message*>(buffer);
    }

    // parse method const
    static const end_of_session_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const end_of_session_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(end_of_session_message::fields_type, time_offset) == 0, "unexpected offset of end_of_session_message::fields_type::time_offset");
static_assert(sizeof(end_of_session_message::fields_type) == 4, "unexpected sizeof end_of_session_message::fields_type");
static_assert(sizeof(end_of_session_message) == sizeof(pitch_multicastdepthofbook::message_header) + 4, "unexpected sizeof end_of_session_message");

#pragma pack(pop)
}
