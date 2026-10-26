#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Second.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Seconds Message
struct seconds_message {

    struct fields_type {
        itch_ntp::second second;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::seconds_message};

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
static_assert(offsetof(seconds_message::fields_type, second) == 0, "unexpected offset of seconds_message::fields_type::second");
static_assert(sizeof(seconds_message::fields_type) == 4, "unexpected sizeof seconds_message::fields_type");
static_assert(sizeof(seconds_message) == sizeof(itch_ntp::message_header) + 4, "unexpected sizeof seconds_message");

#pragma pack(pop)
}
