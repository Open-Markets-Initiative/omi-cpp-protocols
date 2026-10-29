#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/RemainingQuantity.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/Price.hpp"
#include "../types/TradeCondition.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

#pragma pack(push, 1)

// Order Executed At Price Size Message
struct order_executed_at_price_size_message {

    struct fields_type {
        pitch_complex::time_offset time_offset;
        pitch_complex::order_id order_id;
        pitch_complex::executed_quantity executed_quantity;
        pitch_complex::remaining_quantity remaining_quantity;
        pitch_complex::execution_id execution_id;
        pitch_complex::price price;
        pitch_complex::trade_condition trade_condition;
    };

    pitch_complex::message_header header = {std::uint16_t(sizeof(pitch_complex::message_header) + sizeof(fields_type)), message_type::enum_type::order_executed_at_price_size_message};

    fields_type fields;

    // parse method
    static order_executed_at_price_size_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_executed_at_price_size_message*>(buffer);
    }

    // parse method const
    static const order_executed_at_price_size_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_executed_at_price_size_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_executed_at_price_size_message::fields_type, time_offset) == 0, "unexpected offset of order_executed_at_price_size_message::fields_type::time_offset");
static_assert(offsetof(order_executed_at_price_size_message::fields_type, order_id) == 4, "unexpected offset of order_executed_at_price_size_message::fields_type::order_id");
static_assert(offsetof(order_executed_at_price_size_message::fields_type, executed_quantity) == 12, "unexpected offset of order_executed_at_price_size_message::fields_type::executed_quantity");
static_assert(offsetof(order_executed_at_price_size_message::fields_type, remaining_quantity) == 16, "unexpected offset of order_executed_at_price_size_message::fields_type::remaining_quantity");
static_assert(offsetof(order_executed_at_price_size_message::fields_type, execution_id) == 20, "unexpected offset of order_executed_at_price_size_message::fields_type::execution_id");
static_assert(offsetof(order_executed_at_price_size_message::fields_type, price) == 28, "unexpected offset of order_executed_at_price_size_message::fields_type::price");
static_assert(offsetof(order_executed_at_price_size_message::fields_type, trade_condition) == 36, "unexpected offset of order_executed_at_price_size_message::fields_type::trade_condition");
static_assert(sizeof(order_executed_at_price_size_message::fields_type) == 37, "unexpected sizeof order_executed_at_price_size_message::fields_type");
static_assert(sizeof(order_executed_at_price_size_message) == sizeof(pitch_complex::message_header) + 37, "unexpected sizeof order_executed_at_price_size_message");

#pragma pack(pop)
}
