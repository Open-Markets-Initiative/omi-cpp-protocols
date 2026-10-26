#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderBook.hpp"
#include "../types/CrossPrice.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/CrossType.hpp"
#include "../types/NumberOfTrades.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

namespace itch_totalview = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

#pragma pack(push, 1)

// Cross Trade Message
struct cross_trade_message {

    struct fields_type {
        itch_totalview::timestamp timestamp;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::quantity quantity;
        itch_totalview::order_book order_book;
        itch_totalview::cross_price cross_price;
        itch_totalview::match_number match_number;
        itch_totalview::cross_type cross_type;
        itch_totalview::number_of_trades number_of_trades;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::cross_trade_message};

    fields_type fields;

    // parse method
    static cross_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<cross_trade_message*>(buffer);
    }

    // parse method const
    static const cross_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const cross_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(cross_trade_message::fields_type, timestamp) == 0, "unexpected offset of cross_trade_message::fields_type::timestamp");
static_assert(offsetof(cross_trade_message::fields_type, tracking_number) == 8, "unexpected offset of cross_trade_message::fields_type::tracking_number");
static_assert(offsetof(cross_trade_message::fields_type, quantity) == 10, "unexpected offset of cross_trade_message::fields_type::quantity");
static_assert(offsetof(cross_trade_message::fields_type, order_book) == 14, "unexpected offset of cross_trade_message::fields_type::order_book");
static_assert(offsetof(cross_trade_message::fields_type, cross_price) == 18, "unexpected offset of cross_trade_message::fields_type::cross_price");
static_assert(offsetof(cross_trade_message::fields_type, match_number) == 22, "unexpected offset of cross_trade_message::fields_type::match_number");
static_assert(offsetof(cross_trade_message::fields_type, cross_type) == 26, "unexpected offset of cross_trade_message::fields_type::cross_type");
static_assert(offsetof(cross_trade_message::fields_type, number_of_trades) == 27, "unexpected offset of cross_trade_message::fields_type::number_of_trades");
static_assert(sizeof(cross_trade_message::fields_type) == 31, "unexpected sizeof cross_trade_message::fields_type");
static_assert(sizeof(cross_trade_message) == sizeof(itch_totalview::message_header) + 31, "unexpected sizeof cross_trade_message");

#pragma pack(pop)
}
