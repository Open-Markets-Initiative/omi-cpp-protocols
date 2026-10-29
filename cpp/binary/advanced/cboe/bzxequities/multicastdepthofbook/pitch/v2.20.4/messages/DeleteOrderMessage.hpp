#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

namespace pitch_multicastdepthofbook = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4;

#pragma pack(push, 1)

// Delete Order Message
struct delete_order_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::delete_order_message};

    fields_type fields;

    // parse method
    static delete_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<delete_order_message*>(buffer);
    }

    // parse method const
    static const delete_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const delete_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(delete_order_message::fields_type, time_offset) == 0, "unexpected offset of delete_order_message::fields_type::time_offset");
static_assert(offsetof(delete_order_message::fields_type, order_id) == 4, "unexpected offset of delete_order_message::fields_type::order_id");
static_assert(sizeof(delete_order_message::fields_type) == 12, "unexpected sizeof delete_order_message::fields_type");
static_assert(sizeof(delete_order_message) == sizeof(pitch_multicastdepthofbook::message_header) + 12, "unexpected sizeof delete_order_message");

#pragma pack(pop)
}
