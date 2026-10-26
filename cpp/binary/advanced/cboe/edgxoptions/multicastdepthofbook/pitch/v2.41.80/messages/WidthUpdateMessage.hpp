#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/Underlying.hpp"
#include "../types/WidthType.hpp"
#include "../types/Multiplier.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

namespace pitch_multicastdepthofbook = ::cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80;

#pragma pack(push, 1)

// Width Update Message
struct width_update_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::underlying underlying;
        pitch_multicastdepthofbook::width_type width_type;
        pitch_multicastdepthofbook::multiplier multiplier;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::width_update_message};

    fields_type fields;

    // parse method
    static width_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<width_update_message*>(buffer);
    }

    // parse method const
    static const width_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const width_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(width_update_message::fields_type, time_offset) == 0, "unexpected offset of width_update_message::fields_type::time_offset");
static_assert(offsetof(width_update_message::fields_type, underlying) == 4, "unexpected offset of width_update_message::fields_type::underlying");
static_assert(offsetof(width_update_message::fields_type, width_type) == 12, "unexpected offset of width_update_message::fields_type::width_type");
static_assert(offsetof(width_update_message::fields_type, multiplier) == 13, "unexpected offset of width_update_message::fields_type::multiplier");
static_assert(sizeof(width_update_message::fields_type) == 17, "unexpected sizeof width_update_message::fields_type");
static_assert(sizeof(width_update_message) == sizeof(pitch_multicastdepthofbook::message_header) + 17, "unexpected sizeof width_update_message");

#pragma pack(pop)
}
