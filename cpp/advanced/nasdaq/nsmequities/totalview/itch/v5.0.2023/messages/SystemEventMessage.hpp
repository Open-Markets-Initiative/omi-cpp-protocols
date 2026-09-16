#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/EventCode.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// System Event Message
struct system_event_message {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::event_code event_code;
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
static_assert(offsetof(system_event_message::fields_type, stock_locate) == 0, "unexpected offset of system_event_message::fields_type::stock_locate");
static_assert(offsetof(system_event_message::fields_type, tracking_number) == 2, "unexpected offset of system_event_message::fields_type::tracking_number");
static_assert(offsetof(system_event_message::fields_type, timestamp) == 4, "unexpected offset of system_event_message::fields_type::timestamp");
static_assert(offsetof(system_event_message::fields_type, event_code) == 10, "unexpected offset of system_event_message::fields_type::event_code");
static_assert(sizeof(system_event_message::fields_type) == 11, "unexpected sizeof system_event_message::fields_type");
static_assert(sizeof(system_event_message) == sizeof(message_header) + 11, "unexpected sizeof system_event_message");

#pragma pack(pop)
}
