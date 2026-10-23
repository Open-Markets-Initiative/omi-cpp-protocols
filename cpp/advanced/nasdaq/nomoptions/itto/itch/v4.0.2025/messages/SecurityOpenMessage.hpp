#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OptionId.hpp"
#include "../types/OpenState.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Security Open Message
struct security_open_message {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::option_id option_id;
        itch_itto::open_state open_state;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::security_open_message};

    fields_type fields;

    // parse method
    static security_open_message* parse(std::byte* buffer) {
        return reinterpret_cast<security_open_message*>(buffer);
    }

    // parse method const
    static const security_open_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_open_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_open_message::fields_type, tracking_number) == 0, "unexpected offset of security_open_message::fields_type::tracking_number");
static_assert(offsetof(security_open_message::fields_type, timestamp) == 2, "unexpected offset of security_open_message::fields_type::timestamp");
static_assert(offsetof(security_open_message::fields_type, option_id) == 8, "unexpected offset of security_open_message::fields_type::option_id");
static_assert(offsetof(security_open_message::fields_type, open_state) == 12, "unexpected offset of security_open_message::fields_type::open_state");
static_assert(sizeof(security_open_message::fields_type) == 13, "unexpected sizeof security_open_message::fields_type");
static_assert(sizeof(security_open_message) == sizeof(itch_itto::message_header) + 13, "unexpected sizeof security_open_message");

#pragma pack(pop)
}
