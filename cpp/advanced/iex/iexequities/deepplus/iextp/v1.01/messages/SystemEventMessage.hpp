#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SystemEvent.hpp"
#include "../types/Timestamp.hpp"

namespace iex::iexequities::deepplus::iextp::v1_01 {

namespace iextp_deepplus = ::iex::iexequities::deepplus::iextp::v1_01;

#pragma pack(push, 1)

// System Event Message
struct system_event_message {

    struct fields_type {
        iextp_deepplus::system_event system_event;
        iextp_deepplus::timestamp timestamp;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::system_event_message};

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
static_assert(offsetof(system_event_message::fields_type, system_event) == 0, "unexpected offset of system_event_message::fields_type::system_event");
static_assert(offsetof(system_event_message::fields_type, timestamp) == 1, "unexpected offset of system_event_message::fields_type::timestamp");
static_assert(sizeof(system_event_message::fields_type) == 9, "unexpected sizeof system_event_message::fields_type");
static_assert(sizeof(system_event_message) == sizeof(message_header) + 9, "unexpected sizeof system_event_message");

#pragma pack(pop)
}
