#pragma once

#include <cstddef>
#include "../structs/ClientPacketHeader.hpp"
#include "../types/OrderToken.hpp"
#include "../types/Quantity.hpp"
#include "../types/UnsequencedMessageType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

namespace ouch_pts = ::jnx::jnxequities::pts::ouch::v1_11;

#pragma pack(push, 1)

// Cancel Order Message
struct cancel_order_message {

    struct fields_type {
        ouch_pts::order_token order_token;
        ouch_pts::quantity quantity;
    };

    ouch_pts::client_packet_header header = {std::uint16_t(sizeof(ouch_pts::client_packet_header) + sizeof(fields_type) + sizeof(ouch_pts::unsequenced_message_type) - 2), client_packet_type::enum_type::unsequenced_data_packet};
    ouch_pts::unsequenced_message_type unsequenced_message_type = ouch_pts::unsequenced_message_type::enum_type::cancel_order_message;

    fields_type fields;

    // parse method
    static cancel_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<cancel_order_message*>(buffer);
    }

    // parse method const
    static const cancel_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const cancel_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(cancel_order_message::fields_type, order_token) == 0, "unexpected offset of cancel_order_message::fields_type::order_token");
static_assert(offsetof(cancel_order_message::fields_type, quantity) == 4, "unexpected offset of cancel_order_message::fields_type::quantity");
static_assert(sizeof(cancel_order_message::fields_type) == 8, "unexpected sizeof cancel_order_message::fields_type");
static_assert(sizeof(cancel_order_message) == sizeof(ouch_pts::client_packet_header) + sizeof(ouch_pts::unsequenced_message_type) + 8, "unexpected sizeof cancel_order_message");

#pragma pack(pop)
}
