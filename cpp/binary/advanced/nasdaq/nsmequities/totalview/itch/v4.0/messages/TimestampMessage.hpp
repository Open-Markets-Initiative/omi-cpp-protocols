#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Second.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v4_0;

#pragma pack(push, 1)

// Timestamp Message
struct timestamp_message {

    struct fields_type {
        itch_totalview::second second;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::timestamp_message};

    fields_type fields;

    // parse method
    static timestamp_message* parse(std::byte* buffer) {
        return reinterpret_cast<timestamp_message*>(buffer);
    }

    // parse method const
    static const timestamp_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const timestamp_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(timestamp_message::fields_type, second) == 0, "unexpected offset of timestamp_message::fields_type::second");
static_assert(sizeof(timestamp_message::fields_type) == 4, "unexpected sizeof timestamp_message::fields_type");
static_assert(sizeof(timestamp_message) == sizeof(itch_totalview::message_header) + 4, "unexpected sizeof timestamp_message");

#pragma pack(pop)
}
