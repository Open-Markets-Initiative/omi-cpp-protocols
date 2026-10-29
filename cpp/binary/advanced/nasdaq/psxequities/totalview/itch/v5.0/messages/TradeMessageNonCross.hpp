#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Shares.hpp"
#include "../types/Stock.hpp"
#include "../types/Price.hpp"
#include "../types/MatchNumber.hpp"

namespace nasdaq::psxequities::totalview::itch::v5_0 {

namespace itch_totalview = ::nasdaq::psxequities::totalview::itch::v5_0;

#pragma pack(push, 1)

// Trade Message Non Cross
struct trade_message_non_cross {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::order_reference_number order_reference_number;
        itch_totalview::buy_sell_indicator buy_sell_indicator;
        itch_totalview::shares shares;
        itch_totalview::stock stock;
        itch_totalview::price price;
        itch_totalview::match_number match_number;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::trade_message_non_cross};

    fields_type fields;

    // parse method
    static trade_message_non_cross* parse(std::byte* buffer) {
        return reinterpret_cast<trade_message_non_cross*>(buffer);
    }

    // parse method const
    static const trade_message_non_cross* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_message_non_cross*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_message_non_cross::fields_type, stock_locate) == 0, "unexpected offset of trade_message_non_cross::fields_type::stock_locate");
static_assert(offsetof(trade_message_non_cross::fields_type, tracking_number) == 2, "unexpected offset of trade_message_non_cross::fields_type::tracking_number");
static_assert(offsetof(trade_message_non_cross::fields_type, timestamp) == 4, "unexpected offset of trade_message_non_cross::fields_type::timestamp");
static_assert(offsetof(trade_message_non_cross::fields_type, order_reference_number) == 10, "unexpected offset of trade_message_non_cross::fields_type::order_reference_number");
static_assert(offsetof(trade_message_non_cross::fields_type, buy_sell_indicator) == 18, "unexpected offset of trade_message_non_cross::fields_type::buy_sell_indicator");
static_assert(offsetof(trade_message_non_cross::fields_type, shares) == 19, "unexpected offset of trade_message_non_cross::fields_type::shares");
static_assert(offsetof(trade_message_non_cross::fields_type, stock) == 23, "unexpected offset of trade_message_non_cross::fields_type::stock");
static_assert(offsetof(trade_message_non_cross::fields_type, price) == 31, "unexpected offset of trade_message_non_cross::fields_type::price");
static_assert(offsetof(trade_message_non_cross::fields_type, match_number) == 35, "unexpected offset of trade_message_non_cross::fields_type::match_number");
static_assert(sizeof(trade_message_non_cross::fields_type) == 43, "unexpected sizeof trade_message_non_cross::fields_type");
static_assert(sizeof(trade_message_non_cross) == sizeof(itch_totalview::message_header) + 43, "unexpected sizeof trade_message_non_cross");

#pragma pack(pop)
}
