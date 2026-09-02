#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SecurityEvent.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

namespace snap_deep = ::iex::iexequities::deep::snap::v1_6;

#pragma pack(push, 1)

// Security Event Message
struct security_event_message {

    struct fields_type {
        snap_deep::security_event security_event;
        snap_deep::timestamp timestamp;
        snap_deep::symbol symbol;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), {}};

    fields_type fields;

    // parse method
    static security_event_message* parse(std::byte* buffer) {
        return reinterpret_cast<security_event_message*>(buffer);
    }

    // parse method const
    static const security_event_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_event_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_event_message::fields_type, security_event) == 0, "unexpected offset of security_event_message::fields_type::security_event");
static_assert(offsetof(security_event_message::fields_type, timestamp) == 1, "unexpected offset of security_event_message::fields_type::timestamp");
static_assert(offsetof(security_event_message::fields_type, symbol) == 9, "unexpected offset of security_event_message::fields_type::symbol");
static_assert(sizeof(security_event_message::fields_type) == 17, "unexpected sizeof security_event_message::fields_type");
static_assert(sizeof(security_event_message) == sizeof(message_header) + 17, "unexpected sizeof security_event_message");

#pragma pack(pop)
}
