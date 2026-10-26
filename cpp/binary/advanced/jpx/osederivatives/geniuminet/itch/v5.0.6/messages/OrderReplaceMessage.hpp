#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/Side.hpp"
#include "../types/NewOrderbookPosition.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"
#include "../types/OrderAttributes.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

namespace itch_geniuminet = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

#pragma pack(push, 1)

// Order Replace Message
struct order_replace_message {

    struct fields_type {
        itch_geniuminet::nanoseconds nanoseconds;
        itch_geniuminet::order_id order_id;
        itch_geniuminet::order_book_id order_book_id;
        itch_geniuminet::side side;
        itch_geniuminet::new_orderbook_position new_orderbook_position;
        itch_geniuminet::quantity quantity;
        itch_geniuminet::price price;
        itch_geniuminet::order_attributes order_attributes;
    };

    itch_geniuminet::message_header header = {std::uint16_t(sizeof(itch_geniuminet::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_replace_message};

    fields_type fields;

    // parse method
    static order_replace_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_replace_message*>(buffer);
    }

    // parse method const
    static const order_replace_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_replace_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_replace_message::fields_type, nanoseconds) == 0, "unexpected offset of order_replace_message::fields_type::nanoseconds");
static_assert(offsetof(order_replace_message::fields_type, order_id) == 4, "unexpected offset of order_replace_message::fields_type::order_id");
static_assert(offsetof(order_replace_message::fields_type, order_book_id) == 12, "unexpected offset of order_replace_message::fields_type::order_book_id");
static_assert(offsetof(order_replace_message::fields_type, side) == 16, "unexpected offset of order_replace_message::fields_type::side");
static_assert(offsetof(order_replace_message::fields_type, new_orderbook_position) == 17, "unexpected offset of order_replace_message::fields_type::new_orderbook_position");
static_assert(offsetof(order_replace_message::fields_type, quantity) == 21, "unexpected offset of order_replace_message::fields_type::quantity");
static_assert(offsetof(order_replace_message::fields_type, price) == 29, "unexpected offset of order_replace_message::fields_type::price");
static_assert(offsetof(order_replace_message::fields_type, order_attributes) == 33, "unexpected offset of order_replace_message::fields_type::order_attributes");
static_assert(sizeof(order_replace_message::fields_type) == 35, "unexpected sizeof order_replace_message::fields_type");
static_assert(sizeof(order_replace_message) == sizeof(itch_geniuminet::message_header) + 35, "unexpected sizeof order_replace_message");

#pragma pack(pop)
}
