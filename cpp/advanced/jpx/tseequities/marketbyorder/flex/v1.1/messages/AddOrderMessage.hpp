#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeMicroseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"
#include "../types/OrderCondition.hpp"
#include "../types/ModificationFlag.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

// Add Order Message
struct add_order_message {

    struct fields_type {
        flex_marketbyorder::time_microseconds time_microseconds;
        flex_marketbyorder::order_id order_id;
        flex_marketbyorder::side side;
        flex_marketbyorder::quantity quantity;
        flex_marketbyorder::price price;
        flex_marketbyorder::order_condition order_condition;
        flex_marketbyorder::modification_flag modification_flag;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 1), message_type::enum_type::add_order_message};

    fields_type fields;

    // parse method
    static add_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_order_message*>(buffer);
    }

    // parse method const
    static const add_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_order_message::fields_type, time_microseconds) == 0, "unexpected offset of add_order_message::fields_type::time_microseconds");
static_assert(offsetof(add_order_message::fields_type, order_id) == 4, "unexpected offset of add_order_message::fields_type::order_id");
static_assert(offsetof(add_order_message::fields_type, side) == 8, "unexpected offset of add_order_message::fields_type::side");
static_assert(offsetof(add_order_message::fields_type, quantity) == 9, "unexpected offset of add_order_message::fields_type::quantity");
static_assert(offsetof(add_order_message::fields_type, price) == 15, "unexpected offset of add_order_message::fields_type::price");
static_assert(offsetof(add_order_message::fields_type, order_condition) == 23, "unexpected offset of add_order_message::fields_type::order_condition");
static_assert(offsetof(add_order_message::fields_type, modification_flag) == 24, "unexpected offset of add_order_message::fields_type::modification_flag");
static_assert(sizeof(add_order_message::fields_type) == 25, "unexpected sizeof add_order_message::fields_type");
static_assert(sizeof(add_order_message) == sizeof(message_header) + 25, "unexpected sizeof add_order_message");

#pragma pack(pop)
}
