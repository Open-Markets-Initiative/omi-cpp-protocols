// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/TradeCancelledMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/BusinessHeader.hpp"
#include "../types/Symbol.hpp"
#include "../types/TradeNumber.hpp"
#include "../types/TradingSystemTimeStamp.hpp"
#include "../types/ListingMarket.hpp"
#include "../types/ProductType.hpp"
#include "../types/TradeDate.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

// Trade Cancelled Message
struct trade_cancelled_message {

    struct fields_type {
        xmt_quantumfeedlevel2::symbol symbol;
        xmt_quantumfeedlevel2::trade_number trade_number;
        xmt_quantumfeedlevel2::trading_system_time_stamp trading_system_time_stamp;
        xmt_quantumfeedlevel2::listing_market listing_market;
        xmt_quantumfeedlevel2::product_type product_type;
        xmt_quantumfeedlevel2::trade_date trade_date;
    };

    xmt_quantumfeedlevel2::business_header header = {{}, {}, {}, sequence_0(0), {}};

    fields_type fields;

    // parse method
    static trade_cancelled_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_cancelled_message*>(buffer);
    }

    // parse method const
    static const trade_cancelled_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_cancelled_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_cancelled_message::fields_type, symbol) == 0, "unexpected offset of trade_cancelled_message::fields_type::symbol");
static_assert(offsetof(trade_cancelled_message::fields_type, trade_number) == 12, "unexpected offset of trade_cancelled_message::fields_type::trade_number");
static_assert(offsetof(trade_cancelled_message::fields_type, trading_system_time_stamp) == 16, "unexpected offset of trade_cancelled_message::fields_type::trading_system_time_stamp");
static_assert(offsetof(trade_cancelled_message::fields_type, listing_market) == 24, "unexpected offset of trade_cancelled_message::fields_type::listing_market");
static_assert(offsetof(trade_cancelled_message::fields_type, product_type) == 25, "unexpected offset of trade_cancelled_message::fields_type::product_type");
static_assert(offsetof(trade_cancelled_message::fields_type, trade_date) == 26, "unexpected offset of trade_cancelled_message::fields_type::trade_date");
static_assert(sizeof(trade_cancelled_message::fields_type) == 30, "unexpected sizeof trade_cancelled_message::fields_type");
static_assert(sizeof(trade_cancelled_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 30, "unexpected sizeof trade_cancelled_message");

#pragma pack(pop)
}
