#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/EventCode.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// System Event Message
struct system_event_message {

    struct fields_type {
        itch_nlsplus::event_code event_code;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::system_event_message};

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
static_assert(offsetof(system_event_message::fields_type, event_code) == 0, "unexpected offset of system_event_message::fields_type::event_code");
static_assert(sizeof(system_event_message::fields_type) == 1, "unexpected sizeof system_event_message::fields_type");
static_assert(sizeof(system_event_message) == sizeof(itch_nlsplus::message_header) + 1, "unexpected sizeof system_event_message");

#pragma pack(pop)
}
