#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderBook.hpp"
#include "../types/Price.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

namespace itch_totalview = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

#pragma pack(push, 1)

// Add Order Message
struct add_order_message {

    struct fields_type {
        itch_totalview::timestamp timestamp;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::order_reference_number order_reference_number;
        itch_totalview::buy_sell_indicator buy_sell_indicator;
        itch_totalview::quantity quantity;
        itch_totalview::order_book order_book;
        itch_totalview::price price;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::add_order_message};

    fields_type fields;

    // parse method
    static add_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_order_message*>(buffer);
    }

    // parse method const
    static const add_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_order_message::fields_type, timestamp) == 0, "unexpected offset of add_order_message::fields_type::timestamp");
static_assert(offsetof(add_order_message::fields_type, tracking_number) == 8, "unexpected offset of add_order_message::fields_type::tracking_number");
static_assert(offsetof(add_order_message::fields_type, order_reference_number) == 10, "unexpected offset of add_order_message::fields_type::order_reference_number");
static_assert(offsetof(add_order_message::fields_type, buy_sell_indicator) == 18, "unexpected offset of add_order_message::fields_type::buy_sell_indicator");
static_assert(offsetof(add_order_message::fields_type, quantity) == 19, "unexpected offset of add_order_message::fields_type::quantity");
static_assert(offsetof(add_order_message::fields_type, order_book) == 23, "unexpected offset of add_order_message::fields_type::order_book");
static_assert(offsetof(add_order_message::fields_type, price) == 27, "unexpected offset of add_order_message::fields_type::price");
static_assert(sizeof(add_order_message::fields_type) == 31, "unexpected sizeof add_order_message::fields_type");
static_assert(sizeof(add_order_message) == sizeof(itch_totalview::message_header) + 31, "unexpected sizeof add_order_message");

#pragma pack(pop)
}
