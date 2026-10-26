#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/TradeCondition.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

namespace pitch_multicastdepthofbook = ::cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80;

#pragma pack(push, 1)

// Order Executed Message
struct order_executed_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::executed_quantity executed_quantity;
        pitch_multicastdepthofbook::execution_id execution_id;
        pitch_multicastdepthofbook::trade_condition trade_condition;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::order_executed_message};

    fields_type fields;

    // parse method
    static order_executed_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_executed_message*>(buffer);
    }

    // parse method const
    static const order_executed_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_executed_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_executed_message::fields_type, time_offset) == 0, "unexpected offset of order_executed_message::fields_type::time_offset");
static_assert(offsetof(order_executed_message::fields_type, order_id) == 4, "unexpected offset of order_executed_message::fields_type::order_id");
static_assert(offsetof(order_executed_message::fields_type, executed_quantity) == 12, "unexpected offset of order_executed_message::fields_type::executed_quantity");
static_assert(offsetof(order_executed_message::fields_type, execution_id) == 16, "unexpected offset of order_executed_message::fields_type::execution_id");
static_assert(offsetof(order_executed_message::fields_type, trade_condition) == 24, "unexpected offset of order_executed_message::fields_type::trade_condition");
static_assert(sizeof(order_executed_message::fields_type) == 25, "unexpected sizeof order_executed_message::fields_type");
static_assert(sizeof(order_executed_message) == sizeof(pitch_multicastdepthofbook::message_header) + 25, "unexpected sizeof order_executed_message");

#pragma pack(pop)
}
