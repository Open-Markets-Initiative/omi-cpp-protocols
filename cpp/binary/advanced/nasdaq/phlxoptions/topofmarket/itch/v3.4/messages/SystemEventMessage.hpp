#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/EventCode.hpp"
#include "../types/Version.hpp"
#include "../types/Subversion.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

namespace itch_topofmarket = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

#pragma pack(push, 1)

// System Event Message
struct system_event_message {

    struct fields_type {
        itch_topofmarket::nanoseconds nanoseconds;
        itch_topofmarket::event_code event_code;
        itch_topofmarket::version version;
        itch_topofmarket::subversion subversion;
    };

    itch_topofmarket::message_header header = {std::uint16_t(sizeof(itch_topofmarket::message_header) + sizeof(fields_type) - 2), message_type::enum_type::system_event_message};

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
static_assert(offsetof(system_event_message::fields_type, event_code) == 4, "unexpected offset of system_event_message::fields_type::event_code");
static_assert(offsetof(system_event_message::fields_type, version) == 5, "unexpected offset of system_event_message::fields_type::version");
static_assert(offsetof(system_event_message::fields_type, subversion) == 6, "unexpected offset of system_event_message::fields_type::subversion");
static_assert(sizeof(system_event_message::fields_type) == 7, "unexpected sizeof system_event_message::fields_type");
static_assert(sizeof(system_event_message) == sizeof(itch_topofmarket::message_header) + 7, "unexpected sizeof system_event_message");

#pragma pack(pop)
}
