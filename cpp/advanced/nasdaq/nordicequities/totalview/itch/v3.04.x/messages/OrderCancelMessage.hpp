#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/CanceledQuantity.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

namespace itch_totalview = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

#pragma pack(push, 1)

// Order Cancel Message
struct order_cancel_message {

    struct fields_type {
        itch_totalview::timestamp timestamp;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::order_reference_number order_reference_number;
        itch_totalview::canceled_quantity canceled_quantity;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_cancel_message};

    fields_type fields;

    // parse method
    static order_cancel_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_cancel_message*>(buffer);
    }

    // parse method const
    static const order_cancel_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_cancel_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_cancel_message::fields_type, timestamp) == 0, "unexpected offset of order_cancel_message::fields_type::timestamp");
static_assert(offsetof(order_cancel_message::fields_type, tracking_number) == 8, "unexpected offset of order_cancel_message::fields_type::tracking_number");
static_assert(offsetof(order_cancel_message::fields_type, order_reference_number) == 10, "unexpected offset of order_cancel_message::fields_type::order_reference_number");
static_assert(offsetof(order_cancel_message::fields_type, canceled_quantity) == 18, "unexpected offset of order_cancel_message::fields_type::canceled_quantity");
static_assert(sizeof(order_cancel_message::fields_type) == 22, "unexpected sizeof order_cancel_message::fields_type");
static_assert(sizeof(order_cancel_message) == sizeof(itch_totalview::message_header) + 22, "unexpected sizeof order_cancel_message");

#pragma pack(pop)
}
