#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/Group.hpp"
#include "../types/SystemEvent.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

namespace itch_pts = ::jnx::jnxequities::pts::itch::v1_7;

#pragma pack(push, 1)

// System Event Message
struct system_event_message {

    struct fields_type {
        itch_pts::nanoseconds nanoseconds;
        itch_pts::group group;
        itch_pts::system_event system_event;
    };

    itch_pts::message_header header = {std::uint16_t(sizeof(itch_pts::message_header) + sizeof(fields_type) - 2), message_type::enum_type::system_event_message};

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
static_assert(offsetof(system_event_message::fields_type, nanoseconds) == 0, "unexpected offset of system_event_message::fields_type::nanoseconds");
static_assert(offsetof(system_event_message::fields_type, group) == 4, "unexpected offset of system_event_message::fields_type::group");
static_assert(offsetof(system_event_message::fields_type, system_event) == 8, "unexpected offset of system_event_message::fields_type::system_event");
static_assert(sizeof(system_event_message::fields_type) == 9, "unexpected sizeof system_event_message::fields_type");
static_assert(sizeof(system_event_message) == sizeof(itch_pts::message_header) + 9, "unexpected sizeof system_event_message");

#pragma pack(pop)
}
