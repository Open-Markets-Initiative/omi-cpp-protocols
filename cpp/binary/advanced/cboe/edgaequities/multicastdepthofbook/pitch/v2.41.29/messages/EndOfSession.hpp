// Cboe.EdgaEquities.MulticastDepthOfBook.Pitch.v2.41.29: messages/EndOfSession.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

namespace pitch_multicastdepthofbook = ::cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29;

#pragma pack(push, 1)

// End Of Session
struct end_of_session {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::end_of_session};

    fields_type fields;

    // parse method
    static end_of_session* parse(std::byte* buffer) {
        return reinterpret_cast<end_of_session*>(buffer);
    }

    // parse method const
    static const end_of_session* parse(const std::byte* buffer) {
        return reinterpret_cast<const end_of_session*>(buffer);
    }

};

// layout verification
static_assert(offsetof(end_of_session::fields_type, time_offset) == 0, "unexpected offset of end_of_session::fields_type::time_offset");
static_assert(sizeof(end_of_session::fields_type) == 4, "unexpected sizeof end_of_session::fields_type");
static_assert(sizeof(end_of_session) == sizeof(pitch_multicastdepthofbook::message_header) + 4, "unexpected sizeof end_of_session");

#pragma pack(pop)
}
