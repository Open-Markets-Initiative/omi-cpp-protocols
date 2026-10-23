#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/ReferenceNumber.hpp"
#include "../types/CrossNumber.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/Printable.hpp"
#include "../types/PriceLong.hpp"
#include "../types/VolumeLong.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Single Side Executed With Price Message
struct single_side_executed_with_price_message {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::reference_number reference_number;
        itch_itto::cross_number cross_number;
        itch_itto::match_number match_number;
        itch_itto::printable printable;
        itch_itto::price_long price_long;
        itch_itto::volume_long volume_long;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::single_side_executed_with_price_message};

    fields_type fields;

    // parse method
    static single_side_executed_with_price_message* parse(std::byte* buffer) {
        return reinterpret_cast<single_side_executed_with_price_message*>(buffer);
    }

    // parse method const
    static const single_side_executed_with_price_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const single_side_executed_with_price_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(single_side_executed_with_price_message::fields_type, tracking_number) == 0, "unexpected offset of single_side_executed_with_price_message::fields_type::tracking_number");
static_assert(offsetof(single_side_executed_with_price_message::fields_type, timestamp) == 2, "unexpected offset of single_side_executed_with_price_message::fields_type::timestamp");
static_assert(offsetof(single_side_executed_with_price_message::fields_type, reference_number) == 8, "unexpected offset of single_side_executed_with_price_message::fields_type::reference_number");
static_assert(offsetof(single_side_executed_with_price_message::fields_type, cross_number) == 16, "unexpected offset of single_side_executed_with_price_message::fields_type::cross_number");
static_assert(offsetof(single_side_executed_with_price_message::fields_type, match_number) == 20, "unexpected offset of single_side_executed_with_price_message::fields_type::match_number");
static_assert(offsetof(single_side_executed_with_price_message::fields_type, printable) == 24, "unexpected offset of single_side_executed_with_price_message::fields_type::printable");
static_assert(offsetof(single_side_executed_with_price_message::fields_type, price_long) == 25, "unexpected offset of single_side_executed_with_price_message::fields_type::price_long");
static_assert(offsetof(single_side_executed_with_price_message::fields_type, volume_long) == 29, "unexpected offset of single_side_executed_with_price_message::fields_type::volume_long");
static_assert(sizeof(single_side_executed_with_price_message::fields_type) == 33, "unexpected sizeof single_side_executed_with_price_message::fields_type");
static_assert(sizeof(single_side_executed_with_price_message) == sizeof(itch_itto::message_header) + 33, "unexpected sizeof single_side_executed_with_price_message");

#pragma pack(pop)
}
