#pragma once

#include <cstddef>
#include "../structs/ClientPacketHeader.hpp"
#include "../types/OrderToken.hpp"
#include "../types/ClientReference.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderbookId.hpp"
#include "../types/Group.hpp"
#include "../types/Price.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/FirmId.hpp"
#include "../types/Display.hpp"
#include "../types/Capacity.hpp"
#include "../types/MinimumQuantity.hpp"
#include "../types/OrderClassification.hpp"
#include "../types/CashMarginType.hpp"
#include "../types/UnsequencedMessageType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

namespace ouch_pts = ::jnx::jnxequities::pts::ouch::v1_11;

#pragma pack(push, 1)

// Enter Order Message
struct enter_order_message {

    struct fields_type {
        ouch_pts::order_token order_token;
        ouch_pts::client_reference client_reference;
        ouch_pts::buy_sell_indicator buy_sell_indicator;
        ouch_pts::quantity quantity;
        ouch_pts::orderbook_id orderbook_id;
        ouch_pts::group group;
        ouch_pts::price price;
        ouch_pts::time_in_force time_in_force;
        ouch_pts::firm_id firm_id;
        ouch_pts::display display;
        ouch_pts::capacity capacity;
        ouch_pts::minimum_quantity minimum_quantity;
        ouch_pts::order_classification order_classification;
        ouch_pts::cash_margin_type cash_margin_type;
    };

    ouch_pts::client_packet_header header = {std::uint16_t(sizeof(ouch_pts::client_packet_header) + sizeof(fields_type) + sizeof(ouch_pts::unsequenced_message_type) - 2), client_packet_type::enum_type::unsequenced_data_packet};
    ouch_pts::unsequenced_message_type unsequenced_message_type = ouch_pts::unsequenced_message_type::enum_type::enter_order_message;

    fields_type fields;

    // parse method
    static enter_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<enter_order_message*>(buffer);
    }

    // parse method const
    static const enter_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const enter_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(enter_order_message::fields_type, order_token) == 0, "unexpected offset of enter_order_message::fields_type::order_token");
static_assert(offsetof(enter_order_message::fields_type, client_reference) == 4, "unexpected offset of enter_order_message::fields_type::client_reference");
static_assert(offsetof(enter_order_message::fields_type, buy_sell_indicator) == 14, "unexpected offset of enter_order_message::fields_type::buy_sell_indicator");
static_assert(offsetof(enter_order_message::fields_type, quantity) == 15, "unexpected offset of enter_order_message::fields_type::quantity");
static_assert(offsetof(enter_order_message::fields_type, orderbook_id) == 19, "unexpected offset of enter_order_message::fields_type::orderbook_id");
static_assert(offsetof(enter_order_message::fields_type, group) == 23, "unexpected offset of enter_order_message::fields_type::group");
static_assert(offsetof(enter_order_message::fields_type, price) == 27, "unexpected offset of enter_order_message::fields_type::price");
static_assert(offsetof(enter_order_message::fields_type, time_in_force) == 31, "unexpected offset of enter_order_message::fields_type::time_in_force");
static_assert(offsetof(enter_order_message::fields_type, firm_id) == 35, "unexpected offset of enter_order_message::fields_type::firm_id");
static_assert(offsetof(enter_order_message::fields_type, display) == 39, "unexpected offset of enter_order_message::fields_type::display");
static_assert(offsetof(enter_order_message::fields_type, capacity) == 40, "unexpected offset of enter_order_message::fields_type::capacity");
static_assert(offsetof(enter_order_message::fields_type, minimum_quantity) == 41, "unexpected offset of enter_order_message::fields_type::minimum_quantity");
static_assert(offsetof(enter_order_message::fields_type, order_classification) == 45, "unexpected offset of enter_order_message::fields_type::order_classification");
static_assert(offsetof(enter_order_message::fields_type, cash_margin_type) == 46, "unexpected offset of enter_order_message::fields_type::cash_margin_type");
static_assert(sizeof(enter_order_message::fields_type) == 47, "unexpected sizeof enter_order_message::fields_type");
static_assert(sizeof(enter_order_message) == sizeof(ouch_pts::client_packet_header) + sizeof(ouch_pts::unsequenced_message_type) + 47, "unexpected sizeof enter_order_message");

#pragma pack(pop)
}
