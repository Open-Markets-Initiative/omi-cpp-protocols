#pragma once

#include <cstddef>
#include "../structs/ServerPacketHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/SystemEvent.hpp"
#include "../types/SequencedMessageType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

namespace ouch_pts = ::jnx::jnxequities::pts::ouch::v1_11;

#pragma pack(push, 1)

// System Event Message
struct system_event_message {

    struct fields_type {
        ouch_pts::timestamp timestamp;
        ouch_pts::system_event system_event;
    };

    ouch_pts::server_packet_header header = {std::uint16_t(sizeof(ouch_pts::server_packet_header) + sizeof(fields_type) + sizeof(ouch_pts::sequenced_message_type) - 2), server_packet_type::enum_type::sequenced_data_packet};
    ouch_pts::sequenced_message_type sequenced_message_type = ouch_pts::sequenced_message_type::enum_type::system_event_message;

    fields_type fields;

    // parse method
    static system_event_message* parse(std::byte* buffer) {
        return reinterpret_cast<system_event_message*>(buffer);
    }

    // parse method const
    static const system_event_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const system_event_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(system_event_message::fields_type, timestamp) == 0, "unexpected offset of system_event_message::fields_type::timestamp");
static_assert(offsetof(system_event_message::fields_type, system_event) == 8, "unexpected offset of system_event_message::fields_type::system_event");
static_assert(sizeof(system_event_message::fields_type) == 9, "unexpected sizeof system_event_message::fields_type");
static_assert(sizeof(system_event_message) == sizeof(ouch_pts::server_packet_header) + sizeof(ouch_pts::sequenced_message_type) + 9, "unexpected sizeof system_event_message");

#pragma pack(pop)
}
