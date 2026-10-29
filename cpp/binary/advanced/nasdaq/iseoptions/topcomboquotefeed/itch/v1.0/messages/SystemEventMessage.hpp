#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/EventCode.hpp"
#include "../types/CurrentYear.hpp"
#include "../types/CurrentMonth.hpp"
#include "../types/CurrentDay.hpp"
#include "../types/Version.hpp"
#include "../types/SubVersion.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

namespace itch_topcomboquotefeed = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

#pragma pack(push, 1)

// System Event Message
struct system_event_message {

    struct fields_type {
        itch_topcomboquotefeed::timestamp timestamp;
        itch_topcomboquotefeed::event_code event_code;
        itch_topcomboquotefeed::current_year current_year;
        itch_topcomboquotefeed::current_month current_month;
        itch_topcomboquotefeed::current_day current_day;
        itch_topcomboquotefeed::version version;
        itch_topcomboquotefeed::sub_version sub_version;
    };

    itch_topcomboquotefeed::message_header header = {std::uint16_t(sizeof(itch_topcomboquotefeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::system_event_message};

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
static_assert(offsetof(system_event_message::fields_type, event_code) == 6, "unexpected offset of system_event_message::fields_type::event_code");
static_assert(offsetof(system_event_message::fields_type, current_year) == 7, "unexpected offset of system_event_message::fields_type::current_year");
static_assert(offsetof(system_event_message::fields_type, current_month) == 9, "unexpected offset of system_event_message::fields_type::current_month");
static_assert(offsetof(system_event_message::fields_type, current_day) == 10, "unexpected offset of system_event_message::fields_type::current_day");
static_assert(offsetof(system_event_message::fields_type, version) == 11, "unexpected offset of system_event_message::fields_type::version");
static_assert(offsetof(system_event_message::fields_type, sub_version) == 12, "unexpected offset of system_event_message::fields_type::sub_version");
static_assert(sizeof(system_event_message::fields_type) == 13, "unexpected sizeof system_event_message::fields_type");
static_assert(sizeof(system_event_message) == sizeof(itch_topcomboquotefeed::message_header) + 13, "unexpected sizeof system_event_message");

#pragma pack(pop)
}
