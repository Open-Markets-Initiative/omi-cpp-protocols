#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/RemainingQuantity.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/Price.hpp"

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

namespace pitch_multicastdepthofbook = ::cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29;

#pragma pack(push, 1)

// Order Executed At Price Size Message
struct order_executed_at_price_size_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::executed_quantity executed_quantity;
        pitch_multicastdepthofbook::remaining_quantity remaining_quantity;
        pitch_multicastdepthofbook::execution_id execution_id;
        pitch_multicastdepthofbook::price price;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::order_executed_at_price_size_message};

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
static_assert(sizeof(order_executed_at_price_size_message::fields_type) == 36, "unexpected sizeof order_executed_at_price_size_message::fields_type");
static_assert(sizeof(order_executed_at_price_size_message) == sizeof(pitch_multicastdepthofbook::message_header) + 36, "unexpected sizeof order_executed_at_price_size_message");

#pragma pack(pop)
}
