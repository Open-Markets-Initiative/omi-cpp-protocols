#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderBook.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

namespace itch_totalview = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

#pragma pack(push, 1)

// Order Book Flush Message
struct order_book_flush_message {

    struct fields_type {
        itch_totalview::timestamp timestamp;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::order_book order_book;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_book_flush_message};

    fields_type fields;

    // parse method
    static order_book_flush_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_book_flush_message*>(buffer);
    }

    // parse method const
    static const order_book_flush_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_book_flush_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_book_flush_message::fields_type, timestamp) == 0, "unexpected offset of order_book_flush_message::fields_type::timestamp");
static_assert(offsetof(order_book_flush_message::fields_type, tracking_number) == 8, "unexpected offset of order_book_flush_message::fields_type::tracking_number");
static_assert(offsetof(order_book_flush_message::fields_type, order_book) == 10, "unexpected offset of order_book_flush_message::fields_type::order_book");
static_assert(sizeof(order_book_flush_message::fields_type) == 14, "unexpected sizeof order_book_flush_message::fields_type");
static_assert(sizeof(order_book_flush_message) == sizeof(itch_totalview::message_header) + 14, "unexpected sizeof order_book_flush_message");

#pragma pack(pop)
}
