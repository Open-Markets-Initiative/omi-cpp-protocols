#pragma once

#include <cstddef>
#include "../structs/ServerPacketHeader.hpp"
#include "../types/Timestamp.hpp"
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
#include "../types/OrderNumber.hpp"
#include "../types/MinimumQuantity.hpp"
#include "../types/OrderState.hpp"
#include "../types/OrderClassification.hpp"
#include "../types/CashMarginType.hpp"
#include "../types/SequencedMessageType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

namespace ouch_pts = ::jnx::jnxequities::pts::ouch::v1_11;

#pragma pack(push, 1)

// Order Accepted Message
struct order_accepted_message {

    struct fields_type {
        ouch_pts::timestamp timestamp;
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
        ouch_pts::order_number order_number;
        ouch_pts::minimum_quantity minimum_quantity;
        ouch_pts::order_state order_state;
        ouch_pts::order_classification order_classification;
        ouch_pts::cash_margin_type cash_margin_type;
    };

    ouch_pts::server_packet_header header = {std::uint16_t(sizeof(ouch_pts::server_packet_header) + sizeof(fields_type) + sizeof(ouch_pts::sequenced_message_type) - 2), server_packet_type::enum_type::sequenced_data_packet};
    ouch_pts::sequenced_message_type sequenced_message_type = ouch_pts::sequenced_message_type::enum_type::order_accepted_message;

    fields_type fields;

    // parse method
    static order_accepted_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_accepted_message*>(buffer);
    }

    // parse method const
    static const order_accepted_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_accepted_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_accepted_message::fields_type, timestamp) == 0, "unexpected offset of order_accepted_message::fields_type::timestamp");
static_assert(offsetof(order_accepted_message::fields_type, order_token) == 8, "unexpected offset of order_accepted_message::fields_type::order_token");
static_assert(offsetof(order_accepted_message::fields_type, client_reference) == 12, "unexpected offset of order_accepted_message::fields_type::client_reference");
static_assert(offsetof(order_accepted_message::fields_type, buy_sell_indicator) == 22, "unexpected offset of order_accepted_message::fields_type::buy_sell_indicator");
static_assert(offsetof(order_accepted_message::fields_type, quantity) == 23, "unexpected offset of order_accepted_message::fields_type::quantity");
static_assert(offsetof(order_accepted_message::fields_type, orderbook_id) == 27, "unexpected offset of order_accepted_message::fields_type::orderbook_id");
static_assert(offsetof(order_accepted_message::fields_type, group) == 31, "unexpected offset of order_accepted_message::fields_type::group");
static_assert(offsetof(order_accepted_message::fields_type, price) == 35, "unexpected offset of order_accepted_message::fields_type::price");
static_assert(offsetof(order_accepted_message::fields_type, time_in_force) == 39, "unexpected offset of order_accepted_message::fields_type::time_in_force");
static_assert(offsetof(order_accepted_message::fields_type, firm_id) == 43, "unexpected offset of order_accepted_message::fields_type::firm_id");
static_assert(offsetof(order_accepted_message::fields_type, display) == 47, "unexpected offset of order_accepted_message::fields_type::display");
static_assert(offsetof(order_accepted_message::fields_type, capacity) == 48, "unexpected offset of order_accepted_message::fields_type::capacity");
static_assert(offsetof(order_accepted_message::fields_type, order_number) == 49, "unexpected offset of order_accepted_message::fields_type::order_number");
static_assert(offsetof(order_accepted_message::fields_type, minimum_quantity) == 57, "unexpected offset of order_accepted_message::fields_type::minimum_quantity");
static_assert(offsetof(order_accepted_message::fields_type, order_state) == 61, "unexpected offset of order_accepted_message::fields_type::order_state");
static_assert(offsetof(order_accepted_message::fields_type, order_classification) == 62, "unexpected offset of order_accepted_message::fields_type::order_classification");
static_assert(offsetof(order_accepted_message::fields_type, cash_margin_type) == 63, "unexpected offset of order_accepted_message::fields_type::cash_margin_type");
static_assert(sizeof(order_accepted_message::fields_type) == 64, "unexpected sizeof order_accepted_message::fields_type");
static_assert(sizeof(order_accepted_message) == sizeof(ouch_pts::server_packet_header) + sizeof(ouch_pts::sequenced_message_type) + 64, "unexpected sizeof order_accepted_message");

#pragma pack(pop)
}
