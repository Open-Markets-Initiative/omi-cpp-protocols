#pragma once

#include <cstddef>
#include "../structs/ClientPacketHeader.hpp"
#include "../types/ExistingOrderToken.hpp"
#include "../types/ReplacementOrderToken.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/Display.hpp"
#include "../types/MinimumQuantity.hpp"
#include "../types/UnsequencedMessageType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

namespace ouch_pts = ::jnx::jnxequities::pts::ouch::v1_11;

#pragma pack(push, 1)

// Replace Order Message
struct replace_order_message {

    struct fields_type {
        ouch_pts::existing_order_token existing_order_token;
        ouch_pts::replacement_order_token replacement_order_token;
        ouch_pts::quantity quantity;
        ouch_pts::price price;
        ouch_pts::time_in_force time_in_force;
        ouch_pts::display display;
        ouch_pts::minimum_quantity minimum_quantity;
    };

    ouch_pts::client_packet_header header = {std::uint16_t(sizeof(ouch_pts::client_packet_header) + sizeof(fields_type) + sizeof(ouch_pts::unsequenced_message_type) - 2), client_packet_type::enum_type::unsequenced_data_packet};
    ouch_pts::unsequenced_message_type unsequenced_message_type = ouch_pts::unsequenced_message_type::enum_type::replace_order_message;

    fields_type fields;

    // parse method
    static replace_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<replace_order_message*>(buffer);
    }

    // parse method const
    static const replace_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const replace_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(replace_order_message::fields_type, existing_order_token) == 0, "unexpected offset of replace_order_message::fields_type::existing_order_token");
static_assert(offsetof(replace_order_message::fields_type, replacement_order_token) == 4, "unexpected offset of replace_order_message::fields_type::replacement_order_token");
static_assert(offsetof(replace_order_message::fields_type, quantity) == 8, "unexpected offset of replace_order_message::fields_type::quantity");
static_assert(offsetof(replace_order_message::fields_type, price) == 12, "unexpected offset of replace_order_message::fields_type::price");
static_assert(offsetof(replace_order_message::fields_type, time_in_force) == 16, "unexpected offset of replace_order_message::fields_type::time_in_force");
static_assert(offsetof(replace_order_message::fields_type, display) == 20, "unexpected offset of replace_order_message::fields_type::display");
static_assert(offsetof(replace_order_message::fields_type, minimum_quantity) == 21, "unexpected offset of replace_order_message::fields_type::minimum_quantity");
static_assert(sizeof(replace_order_message::fields_type) == 25, "unexpected sizeof replace_order_message::fields_type");
static_assert(sizeof(replace_order_message) == sizeof(ouch_pts::client_packet_header) + sizeof(ouch_pts::unsequenced_message_type) + 25, "unexpected sizeof replace_order_message");

#pragma pack(pop)
}
