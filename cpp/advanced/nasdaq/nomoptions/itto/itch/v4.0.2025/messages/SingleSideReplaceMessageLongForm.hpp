#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OriginalReferenceNumber.hpp"
#include "../types/NewReferenceNumber.hpp"
#include "../types/PriceLong.hpp"
#include "../types/VolumeLong.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Single Side Replace Message Long Form
struct single_side_replace_message_long_form {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::original_reference_number original_reference_number;
        itch_itto::new_reference_number new_reference_number;
        itch_itto::price_long price_long;
        itch_itto::volume_long volume_long;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::single_side_replace_message_long_form};

    fields_type fields;

    // parse method
    static single_side_replace_message_long_form* parse(std::byte* buffer) {
        return reinterpret_cast<single_side_replace_message_long_form*>(buffer);
    }

    // parse method const
    static const single_side_replace_message_long_form* parse(const std::byte* buffer) {
        return reinterpret_cast<const single_side_replace_message_long_form*>(buffer);
    }

};

// layout verification
static_assert(offsetof(single_side_replace_message_long_form::fields_type, tracking_number) == 0, "unexpected offset of single_side_replace_message_long_form::fields_type::tracking_number");
static_assert(offsetof(single_side_replace_message_long_form::fields_type, timestamp) == 2, "unexpected offset of single_side_replace_message_long_form::fields_type::timestamp");
static_assert(offsetof(single_side_replace_message_long_form::fields_type, original_reference_number) == 8, "unexpected offset of single_side_replace_message_long_form::fields_type::original_reference_number");
static_assert(offsetof(single_side_replace_message_long_form::fields_type, new_reference_number) == 16, "unexpected offset of single_side_replace_message_long_form::fields_type::new_reference_number");
static_assert(offsetof(single_side_replace_message_long_form::fields_type, price_long) == 24, "unexpected offset of single_side_replace_message_long_form::fields_type::price_long");
static_assert(offsetof(single_side_replace_message_long_form::fields_type, volume_long) == 28, "unexpected offset of single_side_replace_message_long_form::fields_type::volume_long");
static_assert(sizeof(single_side_replace_message_long_form::fields_type) == 32, "unexpected sizeof single_side_replace_message_long_form::fields_type");
static_assert(sizeof(single_side_replace_message_long_form) == sizeof(itch_itto::message_header) + 32, "unexpected sizeof single_side_replace_message_long_form");

#pragma pack(pop)
}
