#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanosecond.hpp"
#include "../types/OrderId.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/DisplayQuantity.hpp"
#include "../types/TradeMatchId.hpp"
#include "../types/Printable.hpp"
#include "../types/Price.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

// Order Executed With Price Size Message
struct order_executed_with_price_size_message {

    struct fields_type {
        mitch_level2::nanosecond nanosecond;
        mitch_level2::order_id order_id;
        mitch_level2::executed_quantity executed_quantity;
        mitch_level2::display_quantity display_quantity;
        mitch_level2::trade_match_id trade_match_id;
        mitch_level2::printable printable;
        mitch_level2::price price;
    };

    mitch_level2::message_header header = {std::uint16_t(sizeof(mitch_level2::message_header) + sizeof(fields_type)), message_type::enum_type::order_executed_with_price_size_message};

    fields_type fields;

    // parse method
    static order_executed_with_price_size_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_executed_with_price_size_message*>(buffer);
    }

    // parse method const
    static const order_executed_with_price_size_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_executed_with_price_size_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_executed_with_price_size_message::fields_type, nanosecond) == 0, "unexpected offset of order_executed_with_price_size_message::fields_type::nanosecond");
static_assert(offsetof(order_executed_with_price_size_message::fields_type, order_id) == 4, "unexpected offset of order_executed_with_price_size_message::fields_type::order_id");
static_assert(offsetof(order_executed_with_price_size_message::fields_type, executed_quantity) == 12, "unexpected offset of order_executed_with_price_size_message::fields_type::executed_quantity");
static_assert(offsetof(order_executed_with_price_size_message::fields_type, display_quantity) == 16, "unexpected offset of order_executed_with_price_size_message::fields_type::display_quantity");
static_assert(offsetof(order_executed_with_price_size_message::fields_type, trade_match_id) == 20, "unexpected offset of order_executed_with_price_size_message::fields_type::trade_match_id");
static_assert(offsetof(order_executed_with_price_size_message::fields_type, printable) == 28, "unexpected offset of order_executed_with_price_size_message::fields_type::printable");
static_assert(offsetof(order_executed_with_price_size_message::fields_type, price) == 29, "unexpected offset of order_executed_with_price_size_message::fields_type::price");
static_assert(sizeof(order_executed_with_price_size_message::fields_type) == 37, "unexpected sizeof order_executed_with_price_size_message::fields_type");
static_assert(sizeof(order_executed_with_price_size_message) == sizeof(mitch_level2::message_header) + 37, "unexpected sizeof order_executed_with_price_size_message");

#pragma pack(pop)
}
