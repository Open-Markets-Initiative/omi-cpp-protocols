#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/Side.hpp"
#include "../types/OrderId.hpp"
#include "../types/OrderBookPriority.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Add Order Message
struct add_order_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::side side;
        itch_ntp::order_id order_id;
        itch_ntp::order_book_priority order_book_priority;
        itch_ntp::quantity quantity;
        itch_ntp::price price;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::add_order_message};

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
static_assert(offsetof(add_order_message::fields_type, nanoseconds) == 0, "unexpected offset of add_order_message::fields_type::nanoseconds");
static_assert(offsetof(add_order_message::fields_type, trade_date) == 4, "unexpected offset of add_order_message::fields_type::trade_date");
static_assert(offsetof(add_order_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of add_order_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(add_order_message::fields_type, side) == 10, "unexpected offset of add_order_message::fields_type::side");
static_assert(offsetof(add_order_message::fields_type, order_id) == 11, "unexpected offset of add_order_message::fields_type::order_id");
static_assert(offsetof(add_order_message::fields_type, order_book_priority) == 19, "unexpected offset of add_order_message::fields_type::order_book_priority");
static_assert(offsetof(add_order_message::fields_type, quantity) == 27, "unexpected offset of add_order_message::fields_type::quantity");
static_assert(offsetof(add_order_message::fields_type, price) == 31, "unexpected offset of add_order_message::fields_type::price");
static_assert(sizeof(add_order_message::fields_type) == 39, "unexpected sizeof add_order_message::fields_type");
static_assert(sizeof(add_order_message) == sizeof(itch_ntp::message_header) + 39, "unexpected sizeof add_order_message");

#pragma pack(pop)
}
