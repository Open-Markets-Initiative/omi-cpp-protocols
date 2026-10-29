#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderbookId.hpp"
#include "../types/OrderbookCode.hpp"
#include "../types/Group.hpp"
#include "../types/RoundLotSize.hpp"
#include "../types/PriceTickSizeTableId.hpp"
#include "../types/PriceDecimals.hpp"
#include "../types/UpperPriceLimit.hpp"
#include "../types/LowerPriceLimit.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

namespace itch_pts = ::jnx::jnxequities::pts::itch::v1_7;

#pragma pack(push, 1)

// Orderbook Directory Message
struct orderbook_directory_message {

    struct fields_type {
        itch_pts::nanoseconds nanoseconds;
        itch_pts::orderbook_id orderbook_id;
        itch_pts::orderbook_code orderbook_code;
        itch_pts::group group;
        itch_pts::round_lot_size round_lot_size;
        itch_pts::price_tick_size_table_id price_tick_size_table_id;
        itch_pts::price_decimals price_decimals;
        itch_pts::upper_price_limit upper_price_limit;
        itch_pts::lower_price_limit lower_price_limit;
    };

    itch_pts::message_header header = {std::uint16_t(sizeof(itch_pts::message_header) + sizeof(fields_type) - 2), message_type::enum_type::orderbook_directory_message};

    fields_type fields;

    // parse method
    static orderbook_directory_message* parse(std::byte* buffer) {
        return reinterpret_cast<orderbook_directory_message*>(buffer);
    }

    // parse method const
    static const orderbook_directory_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const orderbook_directory_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(orderbook_directory_message::fields_type, nanoseconds) == 0, "unexpected offset of orderbook_directory_message::fields_type::nanoseconds");
static_assert(offsetof(orderbook_directory_message::fields_type, orderbook_id) == 4, "unexpected offset of orderbook_directory_message::fields_type::orderbook_id");
static_assert(offsetof(orderbook_directory_message::fields_type, orderbook_code) == 8, "unexpected offset of orderbook_directory_message::fields_type::orderbook_code");
static_assert(offsetof(orderbook_directory_message::fields_type, group) == 20, "unexpected offset of orderbook_directory_message::fields_type::group");
static_assert(offsetof(orderbook_directory_message::fields_type, round_lot_size) == 24, "unexpected offset of orderbook_directory_message::fields_type::round_lot_size");
static_assert(offsetof(orderbook_directory_message::fields_type, price_tick_size_table_id) == 28, "unexpected offset of orderbook_directory_message::fields_type::price_tick_size_table_id");
static_assert(offsetof(orderbook_directory_message::fields_type, price_decimals) == 32, "unexpected offset of orderbook_directory_message::fields_type::price_decimals");
static_assert(offsetof(orderbook_directory_message::fields_type, upper_price_limit) == 36, "unexpected offset of orderbook_directory_message::fields_type::upper_price_limit");
static_assert(offsetof(orderbook_directory_message::fields_type, lower_price_limit) == 40, "unexpected offset of orderbook_directory_message::fields_type::lower_price_limit");
static_assert(sizeof(orderbook_directory_message::fields_type) == 44, "unexpected sizeof orderbook_directory_message::fields_type");
static_assert(sizeof(orderbook_directory_message) == sizeof(itch_pts::message_header) + 44, "unexpected sizeof orderbook_directory_message");

#pragma pack(pop)
}
