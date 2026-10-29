#pragma once

#include <cstddef>
#include "../types/MessageLength.hpp"
#include "../types/MessageType.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

namespace pitch_multicastdepthofbook = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4;

#pragma pack(push, 1)

struct message_header {

    pitch_multicastdepthofbook::message_length message_length;
    pitch_multicastdepthofbook::message_type message_type;

    // parse method
    static message_header* parse(std::byte* buffer) {
        return reinterpret_cast<message_header*>(buffer);
    }

    // parse method const
    static const message_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const message_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(message_header, message_length) == 0, "unexpected offset of message_header::message_length");
static_assert(offsetof(message_header, message_type) == 1, "unexpected offset of message_header::message_type");
static_assert(sizeof(message_header) == 2, "unexpected sizeof message_header");

#pragma pack(pop)
}
