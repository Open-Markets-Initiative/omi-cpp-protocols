#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/MarketSide.hpp"
#include "../types/OptionId.hpp"
#include "../types/PriceShort.hpp"
#include "../types/VolumeShort.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Add Order Message Short Message Form
struct add_order_message_short_message_form {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::order_reference_number order_reference_number;
        itch_itto::market_side market_side;
        itch_itto::option_id option_id;
        itch_itto::price_short price_short;
        itch_itto::volume_short volume_short;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::add_order_message_short_message_form};

    fields_type fields;

    // parse method
    static add_order_message_short_message_form* parse(std::byte* buffer) {
        return reinterpret_cast<add_order_message_short_message_form*>(buffer);
    }

    // parse method const
    static const add_order_message_short_message_form* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_order_message_short_message_form*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_order_message_short_message_form::fields_type, tracking_number) == 0, "unexpected offset of add_order_message_short_message_form::fields_type::tracking_number");
static_assert(offsetof(add_order_message_short_message_form::fields_type, timestamp) == 2, "unexpected offset of add_order_message_short_message_form::fields_type::timestamp");
static_assert(offsetof(add_order_message_short_message_form::fields_type, order_reference_number) == 8, "unexpected offset of add_order_message_short_message_form::fields_type::order_reference_number");
static_assert(offsetof(add_order_message_short_message_form::fields_type, market_side) == 16, "unexpected offset of add_order_message_short_message_form::fields_type::market_side");
static_assert(offsetof(add_order_message_short_message_form::fields_type, option_id) == 17, "unexpected offset of add_order_message_short_message_form::fields_type::option_id");
static_assert(offsetof(add_order_message_short_message_form::fields_type, price_short) == 21, "unexpected offset of add_order_message_short_message_form::fields_type::price_short");
static_assert(offsetof(add_order_message_short_message_form::fields_type, volume_short) == 23, "unexpected offset of add_order_message_short_message_form::fields_type::volume_short");
static_assert(sizeof(add_order_message_short_message_form::fields_type) == 25, "unexpected sizeof add_order_message_short_message_form::fields_type");
static_assert(sizeof(add_order_message_short_message_form) == sizeof(itch_itto::message_header) + 25, "unexpected sizeof add_order_message_short_message_form");

#pragma pack(pop)
}
