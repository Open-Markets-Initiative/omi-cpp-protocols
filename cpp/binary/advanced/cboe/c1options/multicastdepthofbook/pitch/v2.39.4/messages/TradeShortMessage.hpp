#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/ShortQuantity.hpp"
#include "../types/Symbol.hpp"
#include "../types/ShortPrice.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/TradeCondition.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

namespace pitch_multicastdepthofbook = ::cboe::c1options::multicastdepthofbook::pitch::v2_39_4;

#pragma pack(push, 1)

// Trade Short Message
struct trade_short_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::side_indicator side_indicator;
        pitch_multicastdepthofbook::short_quantity short_quantity;
        pitch_multicastdepthofbook::symbol symbol;
        pitch_multicastdepthofbook::short_price short_price;
        pitch_multicastdepthofbook::execution_id execution_id;
        pitch_multicastdepthofbook::trade_condition trade_condition;
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
static_assert(offsetof(trade_short_message::fields_type, short_quantity) == 13, "unexpected offset of trade_short_message::fields_type::short_quantity");
static_assert(offsetof(trade_short_message::fields_type, symbol) == 15, "unexpected offset of trade_short_message::fields_type::symbol");
static_assert(offsetof(trade_short_message::fields_type, short_price) == 21, "unexpected offset of trade_short_message::fields_type::short_price");
static_assert(offsetof(trade_short_message::fields_type, execution_id) == 23, "unexpected offset of trade_short_message::fields_type::execution_id");
static_assert(offsetof(trade_short_message::fields_type, trade_condition) == 31, "unexpected offset of trade_short_message::fields_type::trade_condition");
static_assert(sizeof(trade_short_message::fields_type) == 32, "unexpected sizeof trade_short_message::fields_type");
static_assert(sizeof(trade_short_message) == sizeof(pitch_multicastdepthofbook::message_header) + 32, "unexpected sizeof trade_short_message");

#pragma pack(pop)
}
