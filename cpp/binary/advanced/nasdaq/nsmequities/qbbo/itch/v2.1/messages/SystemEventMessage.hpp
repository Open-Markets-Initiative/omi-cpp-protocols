#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/EventCode.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

namespace itch_qbbo = ::nasdaq::nsmequities::qbbo::itch::v2_1;

#pragma pack(push, 1)

// System Event Message
struct system_event_message {

    struct fields_type {
        itch_qbbo::tracking_number tracking_number;
        itch_qbbo::time_stamp time_stamp;
        itch_qbbo::event_code event_code;
    };

    itch_qbbo::message_header header = {std::uint16_t(sizeof(itch_qbbo::message_header) + sizeof(fields_type) - 2), message_type::enum_type::system_event_message};

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
static_assert(offsetof(system_event_message::fields_type, tracking_number) == 0, "unexpected offset of system_event_message::fields_type::tracking_number");
static_assert(offsetof(system_event_message::fields_type, time_stamp) == 2, "unexpected offset of system_event_message::fields_type::time_stamp");
static_assert(offsetof(system_event_message::fields_type, event_code) == 8, "unexpected offset of system_event_message::fields_type::event_code");
static_assert(sizeof(system_event_message::fields_type) == 9, "unexpected sizeof system_event_message::fields_type");
static_assert(sizeof(system_event_message) == sizeof(itch_qbbo::message_header) + 9, "unexpected sizeof system_event_message");

#pragma pack(pop)
}
