#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/CrossShares.hpp"
#include "../types/Stock.hpp"
#include "../types/CrossPrice.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/CrossType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Cross Trade Message
struct cross_trade_message {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::cross_shares cross_shares;
        itch_totalview::stock stock;
        itch_totalview::cross_price cross_price;
        itch_totalview::match_number match_number;
        itch_totalview::cross_type cross_type;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::cross_trade_message};

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
static_assert(offsetof(cross_trade_message::fields_type, stock_locate) == 0, "unexpected offset of cross_trade_message::fields_type::stock_locate");
static_assert(offsetof(cross_trade_message::fields_type, tracking_number) == 2, "unexpected offset of cross_trade_message::fields_type::tracking_number");
static_assert(offsetof(cross_trade_message::fields_type, timestamp) == 4, "unexpected offset of cross_trade_message::fields_type::timestamp");
static_assert(offsetof(cross_trade_message::fields_type, cross_shares) == 10, "unexpected offset of cross_trade_message::fields_type::cross_shares");
static_assert(offsetof(cross_trade_message::fields_type, stock) == 18, "unexpected offset of cross_trade_message::fields_type::stock");
static_assert(offsetof(cross_trade_message::fields_type, cross_price) == 26, "unexpected offset of cross_trade_message::fields_type::cross_price");
static_assert(offsetof(cross_trade_message::fields_type, match_number) == 30, "unexpected offset of cross_trade_message::fields_type::match_number");
static_assert(offsetof(cross_trade_message::fields_type, cross_type) == 38, "unexpected offset of cross_trade_message::fields_type::cross_type");
static_assert(sizeof(cross_trade_message::fields_type) == 39, "unexpected sizeof cross_trade_message::fields_type");
static_assert(sizeof(cross_trade_message) == sizeof(message_header) + 39, "unexpected sizeof cross_trade_message");

#pragma pack(pop)
}
