#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/OpenState.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

namespace itch_topofmarket = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

#pragma pack(push, 1)

// Security Open Closed Message
struct security_open_closed_message {

    struct fields_type {
        itch_topofmarket::nanoseconds nanoseconds;
        itch_topofmarket::option_id option_id;
        itch_topofmarket::open_state open_state;
    };

    itch_topofmarket::message_header header = {std::uint16_t(sizeof(itch_topofmarket::message_header) + sizeof(fields_type) - 2), message_type::enum_type::security_open_closed_message};

    fields_type fields;

    // parse method
    static security_open_closed_message* parse(std::byte* buffer) {
        return reinterpret_cast<security_open_closed_message*>(buffer);
    }

    // parse method const
    static const security_open_closed_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_open_closed_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_open_closed_message::fields_type, nanoseconds) == 0, "unexpected offset of security_open_closed_message::fields_type::nanoseconds");
static_assert(offsetof(security_open_closed_message::fields_type, option_id) == 4, "unexpected offset of security_open_closed_message::fields_type::option_id");
static_assert(offsetof(security_open_closed_message::fields_type, open_state) == 8, "unexpected offset of security_open_closed_message::fields_type::open_state");
static_assert(sizeof(security_open_closed_message::fields_type) == 9, "unexpected sizeof security_open_closed_message::fields_type");
static_assert(sizeof(security_open_closed_message) == sizeof(itch_topofmarket::message_header) + 9, "unexpected sizeof security_open_closed_message");

#pragma pack(pop)
}
