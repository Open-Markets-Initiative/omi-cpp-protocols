#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/MarketSide.hpp"
#include "../types/OptionId.hpp"
#include "../types/PriceLong.hpp"
#include "../types/VolumeLong.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Add Order Message Long Form Message
struct add_order_message_long_form_message {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::order_reference_number order_reference_number;
        itch_itto::market_side market_side;
        itch_itto::option_id option_id;
        itch_itto::price_long price_long;
        itch_itto::volume_long volume_long;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::add_order_message_long_form_message};

    fields_type fields;

    // parse method
    static add_order_message_long_form_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_order_message_long_form_message*>(buffer);
    }

    // parse method const
    static const add_order_message_long_form_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_order_message_long_form_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_order_message_long_form_message::fields_type, tracking_number) == 0, "unexpected offset of add_order_message_long_form_message::fields_type::tracking_number");
static_assert(offsetof(add_order_message_long_form_message::fields_type, timestamp) == 2, "unexpected offset of add_order_message_long_form_message::fields_type::timestamp");
static_assert(offsetof(add_order_message_long_form_message::fields_type, order_reference_number) == 8, "unexpected offset of add_order_message_long_form_message::fields_type::order_reference_number");
static_assert(offsetof(add_order_message_long_form_message::fields_type, market_side) == 16, "unexpected offset of add_order_message_long_form_message::fields_type::market_side");
static_assert(offsetof(add_order_message_long_form_message::fields_type, option_id) == 17, "unexpected offset of add_order_message_long_form_message::fields_type::option_id");
static_assert(offsetof(add_order_message_long_form_message::fields_type, price_long) == 21, "unexpected offset of add_order_message_long_form_message::fields_type::price_long");
static_assert(offsetof(add_order_message_long_form_message::fields_type, volume_long) == 25, "unexpected offset of add_order_message_long_form_message::fields_type::volume_long");
static_assert(sizeof(add_order_message_long_form_message::fields_type) == 29, "unexpected sizeof add_order_message_long_form_message::fields_type");
static_assert(sizeof(add_order_message_long_form_message) == sizeof(itch_itto::message_header) + 29, "unexpected sizeof add_order_message_long_form_message");

#pragma pack(pop)
}
