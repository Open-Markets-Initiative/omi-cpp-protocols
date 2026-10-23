#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/EventCode.hpp"
#include "../types/SourceVenue.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

namespace gtp_level2mbo = ::lseg::lse::level2mbo::gtp::v26_2;

#pragma pack(push, 1)

// System Event Message
struct system_event_message {

    struct fields_type {
        gtp_level2mbo::timestamp timestamp;
        gtp_level2mbo::event_code event_code;
        gtp_level2mbo::source_venue source_venue;
    };

    gtp_level2mbo::message_header header = {std::uint16_t(sizeof(gtp_level2mbo::message_header) + sizeof(fields_type)), message_type::enum_type::system_event_message};

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
static_assert(offsetof(system_event_message::fields_type, event_code) == 8, "unexpected offset of system_event_message::fields_type::event_code");
static_assert(offsetof(system_event_message::fields_type, source_venue) == 9, "unexpected offset of system_event_message::fields_type::source_venue");
static_assert(sizeof(system_event_message::fields_type) == 11, "unexpected sizeof system_event_message::fields_type");
static_assert(sizeof(system_event_message) == sizeof(gtp_level2mbo::message_header) + 11, "unexpected sizeof system_event_message");

#pragma pack(pop)
}
