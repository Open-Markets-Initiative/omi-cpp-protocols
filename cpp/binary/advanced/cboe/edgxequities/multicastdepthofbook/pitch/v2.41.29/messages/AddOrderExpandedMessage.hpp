#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/SymbolLong.hpp"
#include "../types/Price.hpp"
#include "../types/AddOrderFlags.hpp"
#include "../types/ParticipantId.hpp"
#include "../types/CustomerIndicator.hpp"

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

namespace pitch_multicastdepthofbook = ::cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29;

#pragma pack(push, 1)

// Add Order Expanded Message
struct add_order_expanded_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::side_indicator side_indicator;
        pitch_multicastdepthofbook::quantity quantity;
        pitch_multicastdepthofbook::symbol_long symbol_long;
        pitch_multicastdepthofbook::price price;
        pitch_multicastdepthofbook::add_order_flags add_order_flags;
        pitch_multicastdepthofbook::participant_id participant_id;
        pitch_multicastdepthofbook::customer_indicator customer_indicator;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::add_order_expanded_message};

    fields_type fields;

    // parse method
    static add_order_expanded_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_order_expanded_message*>(buffer);
    }

    // parse method const
    static const add_order_expanded_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_order_expanded_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_order_expanded_message::fields_type, time_offset) == 0, "unexpected offset of add_order_expanded_message::fields_type::time_offset");
static_assert(offsetof(add_order_expanded_message::fields_type, order_id) == 4, "unexpected offset of add_order_expanded_message::fields_type::order_id");
static_assert(offsetof(add_order_expanded_message::fields_type, side_indicator) == 12, "unexpected offset of add_order_expanded_message::fields_type::side_indicator");
static_assert(offsetof(add_order_expanded_message::fields_type, quantity) == 13, "unexpected offset of add_order_expanded_message::fields_type::quantity");
static_assert(offsetof(add_order_expanded_message::fields_type, symbol_long) == 17, "unexpected offset of add_order_expanded_message::fields_type::symbol_long");
static_assert(offsetof(add_order_expanded_message::fields_type, price) == 25, "unexpected offset of add_order_expanded_message::fields_type::price");
static_assert(offsetof(add_order_expanded_message::fields_type, add_order_flags) == 33, "unexpected offset of add_order_expanded_message::fields_type::add_order_flags");
static_assert(offsetof(add_order_expanded_message::fields_type, participant_id) == 34, "unexpected offset of add_order_expanded_message::fields_type::participant_id");
static_assert(offsetof(add_order_expanded_message::fields_type, customer_indicator) == 38, "unexpected offset of add_order_expanded_message::fields_type::customer_indicator");
static_assert(sizeof(add_order_expanded_message::fields_type) == 39, "unexpected sizeof add_order_expanded_message::fields_type");
static_assert(sizeof(add_order_expanded_message) == sizeof(pitch_multicastdepthofbook::message_header) + 39, "unexpected sizeof add_order_expanded_message");

#pragma pack(pop)
}
