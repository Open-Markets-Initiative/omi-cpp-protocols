#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/SymbolShort.hpp"
#include "../types/Price.hpp"
#include "../types/AddOrderFlags.hpp"

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

namespace pitch_multicastdepthofbook = ::cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29;

#pragma pack(push, 1)

// Add Order Long Message
struct add_order_long_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::side_indicator side_indicator;
        pitch_multicastdepthofbook::quantity quantity;
        pitch_multicastdepthofbook::symbol_short symbol_short;
        pitch_multicastdepthofbook::price price;
        pitch_multicastdepthofbook::add_order_flags add_order_flags;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::add_order_long_message};

    fields_type fields;

    // parse method
    static add_order_long_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_order_long_message*>(buffer);
    }

    // parse method const
    static const add_order_long_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_order_long_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_order_long_message::fields_type, time_offset) == 0, "unexpected offset of add_order_long_message::fields_type::time_offset");
static_assert(offsetof(add_order_long_message::fields_type, order_id) == 4, "unexpected offset of add_order_long_message::fields_type::order_id");
static_assert(offsetof(add_order_long_message::fields_type, side_indicator) == 12, "unexpected offset of add_order_long_message::fields_type::side_indicator");
static_assert(offsetof(add_order_long_message::fields_type, quantity) == 13, "unexpected offset of add_order_long_message::fields_type::quantity");
static_assert(offsetof(add_order_long_message::fields_type, symbol_short) == 17, "unexpected offset of add_order_long_message::fields_type::symbol_short");
static_assert(offsetof(add_order_long_message::fields_type, price) == 23, "unexpected offset of add_order_long_message::fields_type::price");
static_assert(offsetof(add_order_long_message::fields_type, add_order_flags) == 31, "unexpected offset of add_order_long_message::fields_type::add_order_flags");
static_assert(sizeof(add_order_long_message::fields_type) == 32, "unexpected sizeof add_order_long_message::fields_type");
static_assert(sizeof(add_order_long_message) == sizeof(pitch_multicastdepthofbook::message_header) + 32, "unexpected sizeof add_order_long_message");

#pragma pack(pop)
}
