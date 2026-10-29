#pragma once

#include <cstddef>
#include "../structs/ServerPacketHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderToken.hpp"
#include "../types/DecrementQuantity.hpp"
#include "../types/OrderCanceledReason.hpp"
#include "../types/SequencedMessageType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

namespace ouch_pts = ::jnx::jnxequities::pts::ouch::v1_11;

#pragma pack(push, 1)

// Order Canceled Message
struct order_canceled_message {

    struct fields_type {
        ouch_pts::timestamp timestamp;
        ouch_pts::order_token order_token;
        ouch_pts::decrement_quantity decrement_quantity;
        ouch_pts::order_canceled_reason order_canceled_reason;
    };

    ouch_pts::server_packet_header header = {std::uint16_t(sizeof(ouch_pts::server_packet_header) + sizeof(fields_type) + sizeof(ouch_pts::sequenced_message_type) - 2), server_packet_type::enum_type::sequenced_data_packet};
    ouch_pts::sequenced_message_type sequenced_message_type = ouch_pts::sequenced_message_type::enum_type::order_canceled_message;

    fields_type fields;

    // parse method
    static order_canceled_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_canceled_message*>(buffer);
    }

    // parse method const
    static const order_canceled_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_canceled_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_canceled_message::fields_type, timestamp) == 0, "unexpected offset of order_canceled_message::fields_type::timestamp");
static_assert(offsetof(order_canceled_message::fields_type, order_token) == 8, "unexpected offset of order_canceled_message::fields_type::order_token");
static_assert(offsetof(order_canceled_message::fields_type, decrement_quantity) == 12, "unexpected offset of order_canceled_message::fields_type::decrement_quantity");
static_assert(offsetof(order_canceled_message::fields_type, order_canceled_reason) == 16, "unexpected offset of order_canceled_message::fields_type::order_canceled_reason");
static_assert(sizeof(order_canceled_message::fields_type) == 17, "unexpected sizeof order_canceled_message::fields_type");
static_assert(sizeof(order_canceled_message) == sizeof(ouch_pts::server_packet_header) + sizeof(ouch_pts::sequenced_message_type) + 17, "unexpected sizeof order_canceled_message");

#pragma pack(pop)
}
