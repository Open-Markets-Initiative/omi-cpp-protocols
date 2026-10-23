#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Seconds.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

namespace itch_geniuminet = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

#pragma pack(push, 1)

// Seconds Message
struct seconds_message {

    struct fields_type {
        itch_geniuminet::seconds seconds;
    };

    itch_geniuminet::message_header header = {std::uint16_t(sizeof(itch_geniuminet::message_header) + sizeof(fields_type) - 2), message_type::enum_type::seconds_message};

    fields_type fields;

    // parse method
    static seconds_message* parse(std::byte* buffer) {
        return reinterpret_cast<seconds_message*>(buffer);
    }

    // parse method const
    static const seconds_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const seconds_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(seconds_message::fields_type, seconds) == 0, "unexpected offset of seconds_message::fields_type::seconds");
static_assert(sizeof(seconds_message::fields_type) == 4, "unexpected sizeof seconds_message::fields_type");
static_assert(sizeof(seconds_message) == sizeof(itch_geniuminet::message_header) + 4, "unexpected sizeof seconds_message");

#pragma pack(pop)
}
