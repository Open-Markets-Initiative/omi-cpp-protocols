#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/ReferenceNumber.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Single Side Delete Message
struct single_side_delete_message {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::reference_number reference_number;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::single_side_delete_message};

    fields_type fields;

    // parse method
    static single_side_delete_message* parse(std::byte* buffer) {
        return reinterpret_cast<single_side_delete_message*>(buffer);
    }

    // parse method const
    static const single_side_delete_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const single_side_delete_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(single_side_delete_message::fields_type, tracking_number) == 0, "unexpected offset of single_side_delete_message::fields_type::tracking_number");
static_assert(offsetof(single_side_delete_message::fields_type, timestamp) == 2, "unexpected offset of single_side_delete_message::fields_type::timestamp");
static_assert(offsetof(single_side_delete_message::fields_type, reference_number) == 8, "unexpected offset of single_side_delete_message::fields_type::reference_number");
static_assert(sizeof(single_side_delete_message::fields_type) == 16, "unexpected sizeof single_side_delete_message::fields_type");
static_assert(sizeof(single_side_delete_message) == sizeof(itch_itto::message_header) + 16, "unexpected sizeof single_side_delete_message");

#pragma pack(pop)
}
