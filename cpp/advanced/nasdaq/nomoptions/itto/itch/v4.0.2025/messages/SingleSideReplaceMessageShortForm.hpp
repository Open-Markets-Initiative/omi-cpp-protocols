#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OriginalReferenceNumber.hpp"
#include "../types/NewReferenceNumber.hpp"
#include "../types/PriceShort.hpp"
#include "../types/VolumeShort.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Single Side Replace Message Short Form
struct single_side_replace_message_short_form {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::original_reference_number original_reference_number;
        itch_itto::new_reference_number new_reference_number;
        itch_itto::price_short price_short;
        itch_itto::volume_short volume_short;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::single_side_replace_message_short_form};

    fields_type fields;

    // parse method
    static single_side_replace_message_short_form* parse(std::byte* buffer) {
        return reinterpret_cast<single_side_replace_message_short_form*>(buffer);
    }

    // parse method const
    static const single_side_replace_message_short_form* parse(const std::byte* buffer) {
        return reinterpret_cast<const single_side_replace_message_short_form*>(buffer);
    }

};

// layout verification
static_assert(offsetof(single_side_replace_message_short_form::fields_type, tracking_number) == 0, "unexpected offset of single_side_replace_message_short_form::fields_type::tracking_number");
static_assert(offsetof(single_side_replace_message_short_form::fields_type, timestamp) == 2, "unexpected offset of single_side_replace_message_short_form::fields_type::timestamp");
static_assert(offsetof(single_side_replace_message_short_form::fields_type, original_reference_number) == 8, "unexpected offset of single_side_replace_message_short_form::fields_type::original_reference_number");
static_assert(offsetof(single_side_replace_message_short_form::fields_type, new_reference_number) == 16, "unexpected offset of single_side_replace_message_short_form::fields_type::new_reference_number");
static_assert(offsetof(single_side_replace_message_short_form::fields_type, price_short) == 24, "unexpected offset of single_side_replace_message_short_form::fields_type::price_short");
static_assert(offsetof(single_side_replace_message_short_form::fields_type, volume_short) == 26, "unexpected offset of single_side_replace_message_short_form::fields_type::volume_short");
static_assert(sizeof(single_side_replace_message_short_form::fields_type) == 28, "unexpected sizeof single_side_replace_message_short_form::fields_type");
static_assert(sizeof(single_side_replace_message_short_form) == sizeof(itch_itto::message_header) + 28, "unexpected sizeof single_side_replace_message_short_form");

#pragma pack(pop)
}
