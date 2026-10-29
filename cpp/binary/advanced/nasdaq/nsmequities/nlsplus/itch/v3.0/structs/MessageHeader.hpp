#pragma once

#include <cstddef>
#include "../types/MessageLength.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/MessageType.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

struct message_header {

    itch_nlsplus::message_length message_length;
    itch_nlsplus::tracking_number tracking_number;
    itch_nlsplus::timestamp timestamp;
    itch_nlsplus::message_type message_type;

    // parse method
    static message_header* parse(std::byte* buffer) {
        return reinterpret_cast<message_header*>(buffer);
    }

    // parse method const
    static const message_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const message_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(message_header, message_length) == 0, "unexpected offset of message_header::message_length");
static_assert(offsetof(message_header, tracking_number) == 2, "unexpected offset of message_header::tracking_number");
static_assert(offsetof(message_header, timestamp) == 4, "unexpected offset of message_header::timestamp");
static_assert(offsetof(message_header, message_type) == 10, "unexpected offset of message_header::message_type");
static_assert(sizeof(message_header) == 11, "unexpected sizeof message_header");

#pragma pack(pop)
}
