#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/LongQuantity.hpp"
#include "../types/Symbol.hpp"
#include "../types/LongPrice.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/TradeCondition.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

namespace pitch_multicastdepthofbook = ::cboe::c1options::multicastdepthofbook::pitch::v2_39_4;

#pragma pack(push, 1)

// Trade Long Message
struct trade_long_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::side_indicator side_indicator;
        pitch_multicastdepthofbook::long_quantity long_quantity;
        pitch_multicastdepthofbook::symbol symbol;
        pitch_multicastdepthofbook::long_price long_price;
        pitch_multicastdepthofbook::execution_id execution_id;
        pitch_multicastdepthofbook::trade_condition trade_condition;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::trade_long_message};

    fields_type fields;

    // parse method
    static trade_long_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_long_message*>(buffer);
    }

    // parse method const
    static const trade_long_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_long_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_long_message::fields_type, time_offset) == 0, "unexpected offset of trade_long_message::fields_type::time_offset");
static_assert(offsetof(trade_long_message::fields_type, order_id) == 4, "unexpected offset of trade_long_message::fields_type::order_id");
static_assert(offsetof(trade_long_message::fields_type, side_indicator) == 12, "unexpected offset of trade_long_message::fields_type::side_indicator");
static_assert(offsetof(trade_long_message::fields_type, long_quantity) == 13, "unexpected offset of trade_long_message::fields_type::long_quantity");
static_assert(offsetof(trade_long_message::fields_type, symbol) == 17, "unexpected offset of trade_long_message::fields_type::symbol");
static_assert(offsetof(trade_long_message::fields_type, long_price) == 23, "unexpected offset of trade_long_message::fields_type::long_price");
static_assert(offsetof(trade_long_message::fields_type, execution_id) == 31, "unexpected offset of trade_long_message::fields_type::execution_id");
static_assert(offsetof(trade_long_message::fields_type, trade_condition) == 39, "unexpected offset of trade_long_message::fields_type::trade_condition");
static_assert(sizeof(trade_long_message::fields_type) == 40, "unexpected sizeof trade_long_message::fields_type");
static_assert(sizeof(trade_long_message) == sizeof(pitch_multicastdepthofbook::message_header) + 40, "unexpected sizeof trade_long_message");

#pragma pack(pop)
}
