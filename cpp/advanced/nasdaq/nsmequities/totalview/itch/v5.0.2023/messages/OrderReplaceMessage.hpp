#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OriginalOrderReferenceNumber.hpp"
#include "../types/NewOrderReferenceNumber.hpp"
#include "../types/Shares.hpp"
#include "../types/Price.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Order Replace Message
struct order_replace_message {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::original_order_reference_number original_order_reference_number;
        itch_totalview::new_order_reference_number new_order_reference_number;
        itch_totalview::shares shares;
        itch_totalview::price price;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_replace_message};

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
static_assert(offsetof(order_replace_message::fields_type, stock_locate) == 0, "unexpected offset of order_replace_message::fields_type::stock_locate");
static_assert(offsetof(order_replace_message::fields_type, tracking_number) == 2, "unexpected offset of order_replace_message::fields_type::tracking_number");
static_assert(offsetof(order_replace_message::fields_type, timestamp) == 4, "unexpected offset of order_replace_message::fields_type::timestamp");
static_assert(offsetof(order_replace_message::fields_type, original_order_reference_number) == 10, "unexpected offset of order_replace_message::fields_type::original_order_reference_number");
static_assert(offsetof(order_replace_message::fields_type, new_order_reference_number) == 18, "unexpected offset of order_replace_message::fields_type::new_order_reference_number");
static_assert(offsetof(order_replace_message::fields_type, shares) == 26, "unexpected offset of order_replace_message::fields_type::shares");
static_assert(offsetof(order_replace_message::fields_type, price) == 30, "unexpected offset of order_replace_message::fields_type::price");
static_assert(sizeof(order_replace_message::fields_type) == 34, "unexpected sizeof order_replace_message::fields_type");
static_assert(sizeof(order_replace_message) == sizeof(message_header) + 34, "unexpected sizeof order_replace_message");

#pragma pack(pop)
}
