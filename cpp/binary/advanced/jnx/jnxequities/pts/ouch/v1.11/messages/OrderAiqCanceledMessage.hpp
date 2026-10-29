#pragma once

#include <cstddef>
#include "../structs/ServerPacketHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderToken.hpp"
#include "../types/DecrementQuantity.hpp"
#include "../types/OrderCanceledReason.hpp"
#include "../types/QuantityPreventedFromTrading.hpp"
#include "../types/ExecutionPrice.hpp"
#include "../types/LiquidityIndicator.hpp"
#include "../types/SequencedMessageType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

namespace ouch_pts = ::jnx::jnxequities::pts::ouch::v1_11;

#pragma pack(push, 1)

// Order Aiq Canceled Message
struct order_aiq_canceled_message {

    struct fields_type {
        ouch_pts::timestamp timestamp;
        ouch_pts::order_token order_token;
        ouch_pts::decrement_quantity decrement_quantity;
        ouch_pts::order_canceled_reason order_canceled_reason;
        ouch_pts::quantity_prevented_from_trading quantity_prevented_from_trading;
        ouch_pts::execution_price execution_price;
        ouch_pts::liquidity_indicator liquidity_indicator;
    };

    ouch_pts::server_packet_header header = {std::uint16_t(sizeof(ouch_pts::server_packet_header) + sizeof(fields_type) + sizeof(ouch_pts::sequenced_message_type) - 2), server_packet_type::enum_type::sequenced_data_packet};
    ouch_pts::sequenced_message_type sequenced_message_type = ouch_pts::sequenced_message_type::enum_type::order_aiq_canceled_message;

    fields_type fields;

    // parse method
    static order_aiq_canceled_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_aiq_canceled_message*>(buffer);
    }

    // parse method const
    static const order_aiq_canceled_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_aiq_canceled_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_aiq_canceled_message::fields_type, timestamp) == 0, "unexpected offset of order_aiq_canceled_message::fields_type::timestamp");
static_assert(offsetof(order_aiq_canceled_message::fields_type, order_token) == 8, "unexpected offset of order_aiq_canceled_message::fields_type::order_token");
static_assert(offsetof(order_aiq_canceled_message::fields_type, decrement_quantity) == 12, "unexpected offset of order_aiq_canceled_message::fields_type::decrement_quantity");
static_assert(offsetof(order_aiq_canceled_message::fields_type, order_canceled_reason) == 16, "unexpected offset of order_aiq_canceled_message::fields_type::order_canceled_reason");
static_assert(offsetof(order_aiq_canceled_message::fields_type, quantity_prevented_from_trading) == 17, "unexpected offset of order_aiq_canceled_message::fields_type::quantity_prevented_from_trading");
static_assert(offsetof(order_aiq_canceled_message::fields_type, execution_price) == 21, "unexpected offset of order_aiq_canceled_message::fields_type::execution_price");
static_assert(offsetof(order_aiq_canceled_message::fields_type, liquidity_indicator) == 25, "unexpected offset of order_aiq_canceled_message::fields_type::liquidity_indicator");
static_assert(sizeof(order_aiq_canceled_message::fields_type) == 26, "unexpected sizeof order_aiq_canceled_message::fields_type");
static_assert(sizeof(order_aiq_canceled_message) == sizeof(ouch_pts::server_packet_header) + sizeof(ouch_pts::sequenced_message_type) + 26, "unexpected sizeof order_aiq_canceled_message");

#pragma pack(pop)
}
