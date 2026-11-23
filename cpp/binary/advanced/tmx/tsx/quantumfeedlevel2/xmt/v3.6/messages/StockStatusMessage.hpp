// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/StockStatusMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/BusinessHeader.hpp"
#include "../types/Symbol.hpp"
#include "../types/Comment.hpp"
#include "../types/StockState.hpp"
#include "../types/TradingSystemTimeStamp.hpp"
#include "../types/ListingMarket.hpp"
#include "../types/ProductType.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

// Stock Status Message
struct stock_status_message {

    struct fields_type {
        xmt_quantumfeedlevel2::symbol symbol;
        xmt_quantumfeedlevel2::comment comment;
        xmt_quantumfeedlevel2::stock_state stock_state;
        xmt_quantumfeedlevel2::trading_system_time_stamp trading_system_time_stamp;
        xmt_quantumfeedlevel2::listing_market listing_market;
        xmt_quantumfeedlevel2::product_type product_type;
    };

    xmt_quantumfeedlevel2::business_header header = {{}, {}, {}, sequence_0(0), {}};

    fields_type fields;

    // parse method
    static stock_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<stock_status_message*>(buffer);
    }

    // parse method const
    static const stock_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const stock_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(stock_status_message::fields_type, symbol) == 0, "unexpected offset of stock_status_message::fields_type::symbol");
static_assert(offsetof(stock_status_message::fields_type, comment) == 12, "unexpected offset of stock_status_message::fields_type::comment");
static_assert(offsetof(stock_status_message::fields_type, stock_state) == 52, "unexpected offset of stock_status_message::fields_type::stock_state");
static_assert(offsetof(stock_status_message::fields_type, trading_system_time_stamp) == 54, "unexpected offset of stock_status_message::fields_type::trading_system_time_stamp");
static_assert(offsetof(stock_status_message::fields_type, listing_market) == 62, "unexpected offset of stock_status_message::fields_type::listing_market");
static_assert(offsetof(stock_status_message::fields_type, product_type) == 63, "unexpected offset of stock_status_message::fields_type::product_type");
static_assert(sizeof(stock_status_message::fields_type) == 64, "unexpected sizeof stock_status_message::fields_type");
static_assert(sizeof(stock_status_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 64, "unexpected sizeof stock_status_message");

#pragma pack(pop)
}
