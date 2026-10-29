#pragma once

#include <cstddef>
#include "../structs/ServerPacketHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/ReplacementOrderToken.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderbookId.hpp"
#include "../types/Group.hpp"
#include "../types/Price.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/Display.hpp"
#include "../types/OrderNumber.hpp"
#include "../types/MinimumQuantity.hpp"
#include "../types/OrderState.hpp"
#include "../types/PreviousOrderToken.hpp"
#include "../types/SequencedMessageType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

namespace ouch_pts = ::jnx::jnxequities::pts::ouch::v1_11;

#pragma pack(push, 1)

// Order Replaced Message
struct order_replaced_message {

    struct fields_type {
        ouch_pts::timestamp timestamp;
        ouch_pts::replacement_order_token replacement_order_token;
        ouch_pts::buy_sell_indicator buy_sell_indicator;
        ouch_pts::quantity quantity;
        ouch_pts::orderbook_id orderbook_id;
        ouch_pts::group group;
        ouch_pts::price price;
        ouch_pts::time_in_force time_in_force;
        ouch_pts::display display;
        ouch_pts::order_number order_number;
        ouch_pts::minimum_quantity minimum_quantity;
        ouch_pts::order_state order_state;
        ouch_pts::previous_order_token previous_order_token;
    };

    ouch_pts::server_packet_header header = {std::uint16_t(sizeof(ouch_pts::server_packet_header) + sizeof(fields_type) + sizeof(ouch_pts::sequenced_message_type) - 2), server_packet_type::enum_type::sequenced_data_packet};
    ouch_pts::sequenced_message_type sequenced_message_type = ouch_pts::sequenced_message_type::enum_type::order_replaced_message;

    fields_type fields;

    // parse method
    static order_replaced_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_replaced_message*>(buffer);
    }

    // parse method const
    static const order_replaced_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_replaced_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_replaced_message::fields_type, timestamp) == 0, "unexpected offset of order_replaced_message::fields_type::timestamp");
static_assert(offsetof(order_replaced_message::fields_type, replacement_order_token) == 8, "unexpected offset of order_replaced_message::fields_type::replacement_order_token");
static_assert(offsetof(order_replaced_message::fields_type, buy_sell_indicator) == 12, "unexpected offset of order_replaced_message::fields_type::buy_sell_indicator");
static_assert(offsetof(order_replaced_message::fields_type, quantity) == 13, "unexpected offset of order_replaced_message::fields_type::quantity");
static_assert(offsetof(order_replaced_message::fields_type, orderbook_id) == 17, "unexpected offset of order_replaced_message::fields_type::orderbook_id");
static_assert(offsetof(order_replaced_message::fields_type, group) == 21, "unexpected offset of order_replaced_message::fields_type::group");
static_assert(offsetof(order_replaced_message::fields_type, price) == 25, "unexpected offset of order_replaced_message::fields_type::price");
static_assert(offsetof(order_replaced_message::fields_type, time_in_force) == 29, "unexpected offset of order_replaced_message::fields_type::time_in_force");
static_assert(offsetof(order_replaced_message::fields_type, display) == 33, "unexpected offset of order_replaced_message::fields_type::display");
static_assert(offsetof(order_replaced_message::fields_type, order_number) == 34, "unexpected offset of order_replaced_message::fields_type::order_number");
static_assert(offsetof(order_replaced_message::fields_type, minimum_quantity) == 42, "unexpected offset of order_replaced_message::fields_type::minimum_quantity");
static_assert(offsetof(order_replaced_message::fields_type, order_state) == 46, "unexpected offset of order_replaced_message::fields_type::order_state");
static_assert(offsetof(order_replaced_message::fields_type, previous_order_token) == 47, "unexpected offset of order_replaced_message::fields_type::previous_order_token");
static_assert(sizeof(order_replaced_message::fields_type) == 51, "unexpected sizeof order_replaced_message::fields_type");
static_assert(sizeof(order_replaced_message) == sizeof(ouch_pts::server_packet_header) + sizeof(ouch_pts::sequenced_message_type) + 51, "unexpected sizeof order_replaced_message");

#pragma pack(pop)
}
