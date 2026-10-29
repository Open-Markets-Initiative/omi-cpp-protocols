#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderNumber.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderbookId.hpp"
#include "../types/Group.hpp"
#include "../types/Price.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

namespace itch_pts = ::jnx::jnxequities::pts::itch::v1_7;

#pragma pack(push, 1)

// Order Added Without Attributes Message
struct order_added_without_attributes_message {

    struct fields_type {
        itch_pts::nanoseconds nanoseconds;
        itch_pts::order_number order_number;
        itch_pts::buy_sell_indicator buy_sell_indicator;
        itch_pts::quantity quantity;
        itch_pts::orderbook_id orderbook_id;
        itch_pts::group group;
        itch_pts::price price;
    };

    itch_pts::message_header header = {std::uint16_t(sizeof(itch_pts::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_added_without_attributes_message};

    fields_type fields;

    // parse method
    static order_added_without_attributes_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_added_without_attributes_message*>(buffer);
    }

    // parse method const
    static const order_added_without_attributes_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_added_without_attributes_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_added_without_attributes_message::fields_type, nanoseconds) == 0, "unexpected offset of order_added_without_attributes_message::fields_type::nanoseconds");
static_assert(offsetof(order_added_without_attributes_message::fields_type, order_number) == 4, "unexpected offset of order_added_without_attributes_message::fields_type::order_number");
static_assert(offsetof(order_added_without_attributes_message::fields_type, buy_sell_indicator) == 12, "unexpected offset of order_added_without_attributes_message::fields_type::buy_sell_indicator");
static_assert(offsetof(order_added_without_attributes_message::fields_type, quantity) == 13, "unexpected offset of order_added_without_attributes_message::fields_type::quantity");
static_assert(offsetof(order_added_without_attributes_message::fields_type, orderbook_id) == 17, "unexpected offset of order_added_without_attributes_message::fields_type::orderbook_id");
static_assert(offsetof(order_added_without_attributes_message::fields_type, group) == 21, "unexpected offset of order_added_without_attributes_message::fields_type::group");
static_assert(offsetof(order_added_without_attributes_message::fields_type, price) == 25, "unexpected offset of order_added_without_attributes_message::fields_type::price");
static_assert(sizeof(order_added_without_attributes_message::fields_type) == 29, "unexpected sizeof order_added_without_attributes_message::fields_type");
static_assert(sizeof(order_added_without_attributes_message) == sizeof(itch_pts::message_header) + 29, "unexpected sizeof order_added_without_attributes_message");

#pragma pack(pop)
}
