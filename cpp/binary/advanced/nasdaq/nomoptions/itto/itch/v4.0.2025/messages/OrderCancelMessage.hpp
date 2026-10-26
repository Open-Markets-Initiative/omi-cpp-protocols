#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/CancelledContracts.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Order Cancel Message
struct order_cancel_message {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::order_reference_number order_reference_number;
        itch_itto::cancelled_contracts cancelled_contracts;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_cancel_message};

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
static_assert(offsetof(order_cancel_message::fields_type, tracking_number) == 0, "unexpected offset of order_cancel_message::fields_type::tracking_number");
static_assert(offsetof(order_cancel_message::fields_type, timestamp) == 2, "unexpected offset of order_cancel_message::fields_type::timestamp");
static_assert(offsetof(order_cancel_message::fields_type, order_reference_number) == 8, "unexpected offset of order_cancel_message::fields_type::order_reference_number");
static_assert(offsetof(order_cancel_message::fields_type, cancelled_contracts) == 16, "unexpected offset of order_cancel_message::fields_type::cancelled_contracts");
static_assert(sizeof(order_cancel_message::fields_type) == 20, "unexpected sizeof order_cancel_message::fields_type");
static_assert(sizeof(order_cancel_message) == sizeof(itch_itto::message_header) + 20, "unexpected sizeof order_cancel_message");

#pragma pack(pop)
}
