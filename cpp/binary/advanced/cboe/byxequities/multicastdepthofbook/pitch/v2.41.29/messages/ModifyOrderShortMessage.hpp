#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/QuantityShort.hpp"
#include "../types/PriceShort.hpp"
#include "../types/ModifyOrderFlags.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

namespace pitch_multicastdepthofbook = ::cboe::byxequities::multicastdepthofbook::pitch::v2_41_29;

#pragma pack(push, 1)

// Modify Order Short Message
struct modify_order_short_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::quantity_short quantity_short;
        pitch_multicastdepthofbook::price_short price_short;
        pitch_multicastdepthofbook::modify_order_flags modify_order_flags;
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
static_assert(offsetof(modify_order_short_message::fields_type, quantity_short) == 12, "unexpected offset of modify_order_short_message::fields_type::quantity_short");
static_assert(offsetof(modify_order_short_message::fields_type, price_short) == 14, "unexpected offset of modify_order_short_message::fields_type::price_short");
static_assert(offsetof(modify_order_short_message::fields_type, modify_order_flags) == 16, "unexpected offset of modify_order_short_message::fields_type::modify_order_flags");
static_assert(sizeof(modify_order_short_message::fields_type) == 17, "unexpected sizeof modify_order_short_message::fields_type");
static_assert(sizeof(modify_order_short_message) == sizeof(pitch_multicastdepthofbook::message_header) + 17, "unexpected sizeof modify_order_short_message");

#pragma pack(pop)
}
