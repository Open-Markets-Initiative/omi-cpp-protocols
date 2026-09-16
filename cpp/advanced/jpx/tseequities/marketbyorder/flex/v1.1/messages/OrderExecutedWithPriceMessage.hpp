#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeMicroseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/Volume.hpp"
#include "../types/MatchId.hpp"
#include "../types/ExecutionPrice.hpp"
#include "../types/AdoptedPricingMethod.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

// Order Executed With Price Message
struct order_executed_with_price_message {

    struct fields_type {
        flex_marketbyorder::time_microseconds time_microseconds;
        flex_marketbyorder::order_id order_id;
        flex_marketbyorder::side side;
        flex_marketbyorder::volume volume;
        flex_marketbyorder::match_id match_id;
        flex_marketbyorder::execution_price execution_price;
        flex_marketbyorder::adopted_pricing_method adopted_pricing_method;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 1), message_type::enum_type::order_executed_with_price_message};

    fields_type fields;

    // parse method
    static order_executed_with_price_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_executed_with_price_message*>(buffer);
    }

    // parse method const
    static const order_executed_with_price_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_executed_with_price_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_executed_with_price_message::fields_type, time_microseconds) == 0, "unexpected offset of order_executed_with_price_message::fields_type::time_microseconds");
static_assert(offsetof(order_executed_with_price_message::fields_type, order_id) == 4, "unexpected offset of order_executed_with_price_message::fields_type::order_id");
static_assert(offsetof(order_executed_with_price_message::fields_type, side) == 8, "unexpected offset of order_executed_with_price_message::fields_type::side");
static_assert(offsetof(order_executed_with_price_message::fields_type, volume) == 9, "unexpected offset of order_executed_with_price_message::fields_type::volume");
static_assert(offsetof(order_executed_with_price_message::fields_type, match_id) == 15, "unexpected offset of order_executed_with_price_message::fields_type::match_id");
static_assert(offsetof(order_executed_with_price_message::fields_type, execution_price) == 19, "unexpected offset of order_executed_with_price_message::fields_type::execution_price");
static_assert(offsetof(order_executed_with_price_message::fields_type, adopted_pricing_method) == 27, "unexpected offset of order_executed_with_price_message::fields_type::adopted_pricing_method");
static_assert(sizeof(order_executed_with_price_message::fields_type) == 28, "unexpected sizeof order_executed_with_price_message::fields_type");
static_assert(sizeof(order_executed_with_price_message) == sizeof(message_header) + 28, "unexpected sizeof order_executed_with_price_message");

#pragma pack(pop)
}
