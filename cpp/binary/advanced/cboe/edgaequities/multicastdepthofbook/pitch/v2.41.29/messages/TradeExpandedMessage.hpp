#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/SymbolLong.hpp"
#include "../types/Price.hpp"
#include "../types/ExecutionId.hpp"

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

namespace pitch_multicastdepthofbook = ::cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29;

#pragma pack(push, 1)

// Trade Expanded Message
struct trade_expanded_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::side_indicator side_indicator;
        pitch_multicastdepthofbook::quantity quantity;
        pitch_multicastdepthofbook::symbol_long symbol_long;
        pitch_multicastdepthofbook::price price;
        pitch_multicastdepthofbook::execution_id execution_id;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::trade_expanded_message};

    fields_type fields;

    // parse method
    static trade_expanded_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_expanded_message*>(buffer);
    }

    // parse method const
    static const trade_expanded_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_expanded_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_expanded_message::fields_type, time_offset) == 0, "unexpected offset of trade_expanded_message::fields_type::time_offset");
static_assert(offsetof(trade_expanded_message::fields_type, order_id) == 4, "unexpected offset of trade_expanded_message::fields_type::order_id");
static_assert(offsetof(trade_expanded_message::fields_type, side_indicator) == 12, "unexpected offset of trade_expanded_message::fields_type::side_indicator");
static_assert(offsetof(trade_expanded_message::fields_type, quantity) == 13, "unexpected offset of trade_expanded_message::fields_type::quantity");
static_assert(offsetof(trade_expanded_message::fields_type, symbol_long) == 17, "unexpected offset of trade_expanded_message::fields_type::symbol_long");
static_assert(offsetof(trade_expanded_message::fields_type, price) == 25, "unexpected offset of trade_expanded_message::fields_type::price");
static_assert(offsetof(trade_expanded_message::fields_type, execution_id) == 33, "unexpected offset of trade_expanded_message::fields_type::execution_id");
static_assert(sizeof(trade_expanded_message::fields_type) == 41, "unexpected sizeof trade_expanded_message::fields_type");
static_assert(sizeof(trade_expanded_message) == sizeof(pitch_multicastdepthofbook::message_header) + 41, "unexpected sizeof trade_expanded_message");

#pragma pack(pop)
}
