#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/LongQuantity.hpp"
#include "../types/ExpandedSymbol.hpp"
#include "../types/LongPrice.hpp"
#include "../types/AddFlags.hpp"
#include "../types/ParticipantId.hpp"
#include "../types/CustomerIndicator.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

namespace pitch_multicastdepthofbook = ::cboe::c1options::multicastdepthofbook::pitch::v2_39_4;

#pragma pack(push, 1)

// Add Order Expanded Message
struct add_order_expanded_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::side_indicator side_indicator;
        pitch_multicastdepthofbook::long_quantity long_quantity;
        pitch_multicastdepthofbook::expanded_symbol expanded_symbol;
        pitch_multicastdepthofbook::long_price long_price;
        pitch_multicastdepthofbook::add_flags add_flags;
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
static_assert(offsetof(add_order_expanded_message::fields_type, long_quantity) == 13, "unexpected offset of add_order_expanded_message::fields_type::long_quantity");
static_assert(offsetof(add_order_expanded_message::fields_type, expanded_symbol) == 17, "unexpected offset of add_order_expanded_message::fields_type::expanded_symbol");
static_assert(offsetof(add_order_expanded_message::fields_type, long_price) == 25, "unexpected offset of add_order_expanded_message::fields_type::long_price");
static_assert(offsetof(add_order_expanded_message::fields_type, add_flags) == 33, "unexpected offset of add_order_expanded_message::fields_type::add_flags");
static_assert(offsetof(add_order_expanded_message::fields_type, participant_id) == 34, "unexpected offset of add_order_expanded_message::fields_type::participant_id");
static_assert(offsetof(add_order_expanded_message::fields_type, customer_indicator) == 38, "unexpected offset of add_order_expanded_message::fields_type::customer_indicator");
static_assert(sizeof(add_order_expanded_message::fields_type) == 39, "unexpected sizeof add_order_expanded_message::fields_type");
static_assert(sizeof(add_order_expanded_message) == sizeof(pitch_multicastdepthofbook::message_header) + 39, "unexpected sizeof add_order_expanded_message");

#pragma pack(pop)
}
