#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OriginalOrderReferenceNumber.hpp"
#include "../types/NewOrderReferenceNumber.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

namespace itch_totalview = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

#pragma pack(push, 1)

// Order Replace Message
struct order_replace_message {

    struct fields_type {
        itch_totalview::timestamp timestamp;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::original_order_reference_number original_order_reference_number;
        itch_totalview::new_order_reference_number new_order_reference_number;
        itch_totalview::quantity quantity;
        itch_totalview::price price;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_replace_message};

    fields_type fields;

    // parse method
    static order_replace_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_replace_message*>(buffer);
    }

    // parse method const
    static const order_replace_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_replace_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_replace_message::fields_type, timestamp) == 0, "unexpected offset of order_replace_message::fields_type::timestamp");
static_assert(offsetof(order_replace_message::fields_type, tracking_number) == 8, "unexpected offset of order_replace_message::fields_type::tracking_number");
static_assert(offsetof(order_replace_message::fields_type, original_order_reference_number) == 10, "unexpected offset of order_replace_message::fields_type::original_order_reference_number");
static_assert(offsetof(order_replace_message::fields_type, new_order_reference_number) == 18, "unexpected offset of order_replace_message::fields_type::new_order_reference_number");
static_assert(offsetof(order_replace_message::fields_type, quantity) == 26, "unexpected offset of order_replace_message::fields_type::quantity");
static_assert(offsetof(order_replace_message::fields_type, price) == 30, "unexpected offset of order_replace_message::fields_type::price");
static_assert(sizeof(order_replace_message::fields_type) == 34, "unexpected sizeof order_replace_message::fields_type");
static_assert(sizeof(order_replace_message) == sizeof(itch_totalview::message_header) + 34, "unexpected sizeof order_replace_message");

#pragma pack(pop)
}
