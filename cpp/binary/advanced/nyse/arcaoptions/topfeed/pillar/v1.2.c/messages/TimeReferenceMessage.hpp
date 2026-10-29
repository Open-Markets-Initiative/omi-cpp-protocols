#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Id.hpp"
#include "../types/Reserved4.hpp"
#include "../types/SourceTime.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

namespace pillar_topfeed = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

#pragma pack(push, 1)

// Time Reference Message
struct time_reference_message {

    struct fields_type {
        pillar_topfeed::id id;
        pillar_topfeed::reserved_4 reserved_4;
        pillar_topfeed::source_time source_time;
    };

    pillar_topfeed::message_header header = {std::uint16_t(sizeof(pillar_topfeed::message_header) + sizeof(fields_type)), message_type::enum_type::time_reference_message};

    fields_type fields;

    // parse method
    static time_reference_message* parse(std::byte* buffer) {
        return reinterpret_cast<time_reference_message*>(buffer);
    }

    // parse method const
    static const time_reference_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const time_reference_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(time_reference_message::fields_type, id) == 0, "unexpected offset of time_reference_message::fields_type::id");
static_assert(offsetof(time_reference_message::fields_type, reserved_4) == 4, "unexpected offset of time_reference_message::fields_type::reserved_4");
static_assert(offsetof(time_reference_message::fields_type, source_time) == 8, "unexpected offset of time_reference_message::fields_type::source_time");
static_assert(sizeof(time_reference_message::fields_type) == 12, "unexpected sizeof time_reference_message::fields_type");
static_assert(sizeof(time_reference_message) == sizeof(pillar_topfeed::message_header) + 12, "unexpected sizeof time_reference_message");

#pragma pack(pop)
}
