#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanosecond.hpp"
#include "../types/EventCode.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

// System Event Message
struct system_event_message {

    struct fields_type {
        mitch_level2::nanosecond nanosecond;
        mitch_level2::event_code event_code;
    };

    mitch_level2::message_header header = {std::uint16_t(sizeof(mitch_level2::message_header) + sizeof(fields_type)), message_type::enum_type::system_event_message};

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
static_assert(offsetof(system_event_message::fields_type, nanosecond) == 0, "unexpected offset of system_event_message::fields_type::nanosecond");
static_assert(offsetof(system_event_message::fields_type, event_code) == 4, "unexpected offset of system_event_message::fields_type::event_code");
static_assert(sizeof(system_event_message::fields_type) == 5, "unexpected sizeof system_event_message::fields_type");
static_assert(sizeof(system_event_message) == sizeof(mitch_level2::message_header) + 5, "unexpected sizeof system_event_message");

#pragma pack(pop)
}
