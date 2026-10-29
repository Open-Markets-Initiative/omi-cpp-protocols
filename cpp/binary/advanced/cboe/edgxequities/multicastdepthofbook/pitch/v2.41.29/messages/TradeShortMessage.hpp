#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/QuantityShort.hpp"
#include "../types/SymbolShort.hpp"
#include "../types/PriceShort.hpp"
#include "../types/ExecutionId.hpp"

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

namespace pitch_multicastdepthofbook = ::cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29;

#pragma pack(push, 1)

// Trade Short Message
struct trade_short_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::side_indicator side_indicator;
        pitch_multicastdepthofbook::quantity_short quantity_short;
        pitch_multicastdepthofbook::symbol_short symbol_short;
        pitch_multicastdepthofbook::price_short price_short;
        pitch_multicastdepthofbook::execution_id execution_id;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::trade_short_message};

    fields_type fields;

    // parse method
    static trade_short_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_short_message*>(buffer);
    }

    // parse method const
    static const trade_short_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_short_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_short_message::fields_type, time_offset) == 0, "unexpected offset of trade_short_message::fields_type::time_offset");
static_assert(offsetof(trade_short_message::fields_type, order_id) == 4, "unexpected offset of trade_short_message::fields_type::order_id");
static_assert(offsetof(trade_short_message::fields_type, side_indicator) == 12, "unexpected offset of trade_short_message::fields_type::side_indicator");
static_assert(offsetof(trade_short_message::fields_type, quantity_short) == 13, "unexpected offset of trade_short_message::fields_type::quantity_short");
static_assert(offsetof(trade_short_message::fields_type, symbol_short) == 15, "unexpected offset of trade_short_message::fields_type::symbol_short");
static_assert(offsetof(trade_short_message::fields_type, price_short) == 21, "unexpected offset of trade_short_message::fields_type::price_short");
static_assert(offsetof(trade_short_message::fields_type, execution_id) == 23, "unexpected offset of trade_short_message::fields_type::execution_id");
static_assert(sizeof(trade_short_message::fields_type) == 31, "unexpected sizeof trade_short_message::fields_type");
static_assert(sizeof(trade_short_message) == sizeof(pitch_multicastdepthofbook::message_header) + 31, "unexpected sizeof trade_short_message");

#pragma pack(pop)
}
