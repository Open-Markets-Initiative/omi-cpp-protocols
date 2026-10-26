#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

namespace pitch_multicastdepthofbook = ::cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80;

#pragma pack(push, 1)

// Unit Clear Message
struct unit_clear_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::unit_clear_message};

    fields_type fields;

    // parse method
    static unit_clear_message* parse(std::byte* buffer) {
        return reinterpret_cast<unit_clear_message*>(buffer);
    }

    // parse method const
    static const unit_clear_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const unit_clear_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(unit_clear_message::fields_type, time_offset) == 0, "unexpected offset of unit_clear_message::fields_type::time_offset");
static_assert(sizeof(unit_clear_message::fields_type) == 4, "unexpected sizeof unit_clear_message::fields_type");
static_assert(sizeof(unit_clear_message) == sizeof(pitch_multicastdepthofbook::message_header) + 4, "unexpected sizeof unit_clear_message");

#pragma pack(pop)
}
