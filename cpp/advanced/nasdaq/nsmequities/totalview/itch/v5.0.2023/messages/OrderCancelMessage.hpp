#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/CanceledShares.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Order Cancel Message
struct order_cancel_message {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::order_reference_number order_reference_number;
        itch_totalview::canceled_shares canceled_shares;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_cancel_message};

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
static_assert(offsetof(order_cancel_message::fields_type, stock_locate) == 0, "unexpected offset of order_cancel_message::fields_type::stock_locate");
static_assert(offsetof(order_cancel_message::fields_type, tracking_number) == 2, "unexpected offset of order_cancel_message::fields_type::tracking_number");
static_assert(offsetof(order_cancel_message::fields_type, timestamp) == 4, "unexpected offset of order_cancel_message::fields_type::timestamp");
static_assert(offsetof(order_cancel_message::fields_type, order_reference_number) == 10, "unexpected offset of order_cancel_message::fields_type::order_reference_number");
static_assert(offsetof(order_cancel_message::fields_type, canceled_shares) == 18, "unexpected offset of order_cancel_message::fields_type::canceled_shares");
static_assert(sizeof(order_cancel_message::fields_type) == 22, "unexpected sizeof order_cancel_message::fields_type");
static_assert(sizeof(order_cancel_message) == sizeof(message_header) + 22, "unexpected sizeof order_cancel_message");

#pragma pack(pop)
}
