#pragma once

#include <cstddef>
#include "../structs/ServerPacketHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderToken.hpp"
#include "../types/OrderRejectedReason.hpp"
#include "../types/SequencedMessageType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

namespace ouch_pts = ::jnx::jnxequities::pts::ouch::v1_11;

#pragma pack(push, 1)

// Order Rejected Message
struct order_rejected_message {

    struct fields_type {
        ouch_pts::timestamp timestamp;
        ouch_pts::order_token order_token;
        ouch_pts::order_rejected_reason order_rejected_reason;
    };

    ouch_pts::server_packet_header header = {std::uint16_t(sizeof(ouch_pts::server_packet_header) + sizeof(fields_type) + sizeof(ouch_pts::sequenced_message_type) - 2), server_packet_type::enum_type::sequenced_data_packet};
    ouch_pts::sequenced_message_type sequenced_message_type = ouch_pts::sequenced_message_type::enum_type::order_rejected_message;

    fields_type fields;

    // parse method
    static order_rejected_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_rejected_message*>(buffer);
    }

    // parse method const
    static const order_rejected_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_rejected_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_rejected_message::fields_type, timestamp) == 0, "unexpected offset of order_rejected_message::fields_type::timestamp");
static_assert(offsetof(order_rejected_message::fields_type, order_token) == 8, "unexpected offset of order_rejected_message::fields_type::order_token");
static_assert(offsetof(order_rejected_message::fields_type, order_rejected_reason) == 12, "unexpected offset of order_rejected_message::fields_type::order_rejected_reason");
static_assert(sizeof(order_rejected_message::fields_type) == 13, "unexpected sizeof order_rejected_message::fields_type");
static_assert(sizeof(order_rejected_message) == sizeof(ouch_pts::server_packet_header) + sizeof(ouch_pts::sequenced_message_type) + 13, "unexpected sizeof order_rejected_message");

#pragma pack(pop)
}
