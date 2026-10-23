#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/QuantityLong.hpp"
#include "../types/PriceLong.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

namespace pitch_multicastdepthofbook = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

#pragma pack(push, 1)

// Modify Order Long Message
struct modify_order_long_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::quantity_long quantity_long;
        pitch_multicastdepthofbook::price_long price_long;
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
static_assert(offsetof(modify_order_long_message::fields_type, quantity_long) == 12, "unexpected offset of modify_order_long_message::fields_type::quantity_long");
static_assert(offsetof(modify_order_long_message::fields_type, price_long) == 16, "unexpected offset of modify_order_long_message::fields_type::price_long");
static_assert(sizeof(modify_order_long_message::fields_type) == 24, "unexpected sizeof modify_order_long_message::fields_type");
static_assert(sizeof(modify_order_long_message) == sizeof(pitch_multicastdepthofbook::message_header) + 24, "unexpected sizeof modify_order_long_message");

#pragma pack(pop)
}
