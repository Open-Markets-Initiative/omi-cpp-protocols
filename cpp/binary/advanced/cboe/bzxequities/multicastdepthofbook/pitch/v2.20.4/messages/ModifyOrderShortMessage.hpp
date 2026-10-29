#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/QuantityBinary2.hpp"
#include "../types/PriceBinaryShortPrice2.hpp"
#include "../types/ModifyFlags.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

namespace pitch_multicastdepthofbook = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4;

#pragma pack(push, 1)

// Modify Order Short Message
struct modify_order_short_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::quantity_binary_2 quantity_binary_2;
        pitch_multicastdepthofbook::price_binary_short_price_2 price_binary_short_price_2;
        pitch_multicastdepthofbook::modify_flags modify_flags;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::modify_order_short_message};

    fields_type fields;

    // parse method
    static modify_order_short_message* parse(std::byte* buffer) {
        return reinterpret_cast<modify_order_short_message*>(buffer);
    }

    // parse method const
    static const modify_order_short_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const modify_order_short_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(modify_order_short_message::fields_type, time_offset) == 0, "unexpected offset of modify_order_short_message::fields_type::time_offset");
static_assert(offsetof(modify_order_short_message::fields_type, order_id) == 4, "unexpected offset of modify_order_short_message::fields_type::order_id");
static_assert(offsetof(modify_order_short_message::fields_type, quantity_binary_2) == 12, "unexpected offset of modify_order_short_message::fields_type::quantity_binary_2");
static_assert(offsetof(modify_order_short_message::fields_type, price_binary_short_price_2) == 14, "unexpected offset of modify_order_short_message::fields_type::price_binary_short_price_2");
static_assert(offsetof(modify_order_short_message::fields_type, modify_flags) == 16, "unexpected offset of modify_order_short_message::fields_type::modify_flags");
static_assert(sizeof(modify_order_short_message::fields_type) == 17, "unexpected sizeof modify_order_short_message::fields_type");
static_assert(sizeof(modify_order_short_message) == sizeof(pitch_multicastdepthofbook::message_header) + 17, "unexpected sizeof modify_order_short_message");

#pragma pack(pop)
}
