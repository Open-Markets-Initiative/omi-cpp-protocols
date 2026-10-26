#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Seconds.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

// Time Message
struct time_message {

    struct fields_type {
        mitch_level2::seconds seconds;
    };

    mitch_level2::message_header header = {std::uint16_t(sizeof(mitch_level2::message_header) + sizeof(fields_type)), message_type::enum_type::time_message};

    fields_type fields;

    // parse method
    static time_message* parse(std::byte* buffer) {
        return reinterpret_cast<time_message*>(buffer);
    }

    // parse method const
    static const time_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const time_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(time_message::fields_type, seconds) == 0, "unexpected offset of time_message::fields_type::seconds");
static_assert(sizeof(time_message::fields_type) == 4, "unexpected sizeof time_message::fields_type");
static_assert(sizeof(time_message) == sizeof(mitch_level2::message_header) + 4, "unexpected sizeof time_message");

#pragma pack(pop)
}
