#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/QuantityBinary4.hpp"
#include "../types/PriceBinaryLongPrice8.hpp"
#include "../types/ModifyFlags.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

namespace pitch_multicastdepthofbook = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4;

#pragma pack(push, 1)

// Modify Order Long Message
struct modify_order_long_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::quantity_binary_4 quantity_binary_4;
        pitch_multicastdepthofbook::price_binary_long_price_8 price_binary_long_price_8;
        pitch_multicastdepthofbook::modify_flags modify_flags;
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
static_assert(offsetof(modify_order_long_message::fields_type, quantity_binary_4) == 12, "unexpected offset of modify_order_long_message::fields_type::quantity_binary_4");
static_assert(offsetof(modify_order_long_message::fields_type, price_binary_long_price_8) == 16, "unexpected offset of modify_order_long_message::fields_type::price_binary_long_price_8");
static_assert(offsetof(modify_order_long_message::fields_type, modify_flags) == 24, "unexpected offset of modify_order_long_message::fields_type::modify_flags");
static_assert(sizeof(modify_order_long_message::fields_type) == 25, "unexpected sizeof modify_order_long_message::fields_type");
static_assert(sizeof(modify_order_long_message) == sizeof(pitch_multicastdepthofbook::message_header) + 25, "unexpected sizeof modify_order_long_message");

#pragma pack(pop)
}
