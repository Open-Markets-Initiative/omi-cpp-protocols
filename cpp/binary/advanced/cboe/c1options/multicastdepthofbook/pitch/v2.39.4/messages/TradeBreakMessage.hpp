#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/ExecutionId.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

namespace pitch_multicastdepthofbook = ::cboe::c1options::multicastdepthofbook::pitch::v2_39_4;

#pragma pack(push, 1)

// Trade Break Message
struct trade_break_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::execution_id execution_id;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::trade_break_message};

    fields_type fields;

    // parse method
    static trade_break_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_break_message*>(buffer);
    }

    // parse method const
    static const trade_break_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_break_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_break_message::fields_type, time_offset) == 0, "unexpected offset of trade_break_message::fields_type::time_offset");
static_assert(offsetof(trade_break_message::fields_type, execution_id) == 4, "unexpected offset of trade_break_message::fields_type::execution_id");
static_assert(sizeof(trade_break_message::fields_type) == 12, "unexpected sizeof trade_break_message::fields_type");
static_assert(sizeof(trade_break_message) == sizeof(pitch_multicastdepthofbook::message_header) + 12, "unexpected sizeof trade_break_message");

#pragma pack(pop)
}
