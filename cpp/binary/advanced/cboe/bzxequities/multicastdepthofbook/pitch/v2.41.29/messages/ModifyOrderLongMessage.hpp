#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"
#include "../types/ModifyOrderFlags.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

namespace pitch_multicastdepthofbook = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29;

#pragma pack(push, 1)

// Modify Order Long Message
struct modify_order_long_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::quantity quantity;
        pitch_multicastdepthofbook::price price;
        pitch_multicastdepthofbook::modify_order_flags modify_order_flags;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::modify_order_long_message};

    fields_type fields;

    // parse method
    static modify_order_long_message* parse(std::byte* buffer) {
        return reinterpret_cast<modify_order_long_message*>(buffer);
    }

    // parse method const
    static const modify_order_long_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const modify_order_long_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(modify_order_long_message::fields_type, time_offset) == 0, "unexpected offset of modify_order_long_message::fields_type::time_offset");
static_assert(offsetof(modify_order_long_message::fields_type, order_id) == 4, "unexpected offset of modify_order_long_message::fields_type::order_id");
static_assert(offsetof(modify_order_long_message::fields_type, quantity) == 12, "unexpected offset of modify_order_long_message::fields_type::quantity");
static_assert(offsetof(modify_order_long_message::fields_type, price) == 16, "unexpected offset of modify_order_long_message::fields_type::price");
static_assert(offsetof(modify_order_long_message::fields_type, modify_order_flags) == 24, "unexpected offset of modify_order_long_message::fields_type::modify_order_flags");
static_assert(sizeof(modify_order_long_message::fields_type) == 25, "unexpected sizeof modify_order_long_message::fields_type");
static_assert(sizeof(modify_order_long_message) == sizeof(pitch_multicastdepthofbook::message_header) + 25, "unexpected sizeof modify_order_long_message");

#pragma pack(pop)
}
