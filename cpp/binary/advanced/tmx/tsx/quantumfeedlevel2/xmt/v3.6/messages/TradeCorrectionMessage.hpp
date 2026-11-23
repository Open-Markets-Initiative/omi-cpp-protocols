// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/TradeCorrectionMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/BusinessHeader.hpp"
#include "../types/Symbol.hpp"
#include "../types/TradeNumber.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/BuyBrokerNumber.hpp"
#include "../types/SellBrokerNumber.hpp"
#include "../types/InitiatedBy.hpp"
#include "../types/OrigTradeNumber.hpp"
#include "../types/Bypass.hpp"
#include "../types/TradeTimeStamp.hpp"
#include "../types/CrossType.hpp"
#include "../types/TradingSystemTimeStamp.hpp"
#include "../types/ListingMarket.hpp"
#include "../types/ProductType.hpp"
#include "../types/TradeDate.hpp"
#include "../types/IsMidOnly.hpp"
#include "../types/IsDark.hpp"
#include "../types/IsConditional.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

// Trade Correction Message
struct trade_correction_message {

    struct fields_type {
        xmt_quantumfeedlevel2::symbol symbol;
        xmt_quantumfeedlevel2::trade_number trade_number;
        xmt_quantumfeedlevel2::price price;
        xmt_quantumfeedlevel2::volume volume;
        xmt_quantumfeedlevel2::buy_broker_number buy_broker_number;
        xmt_quantumfeedlevel2::sell_broker_number sell_broker_number;
        xmt_quantumfeedlevel2::initiated_by initiated_by;
        xmt_quantumfeedlevel2::orig_trade_number orig_trade_number;
        xmt_quantumfeedlevel2::bypass bypass;
        xmt_quantumfeedlevel2::trade_time_stamp trade_time_stamp;
        xmt_quantumfeedlevel2::cross_type cross_type;
        xmt_quantumfeedlevel2::trading_system_time_stamp trading_system_time_stamp;
        xmt_quantumfeedlevel2::listing_market listing_market;
        xmt_quantumfeedlevel2::product_type product_type;
        xmt_quantumfeedlevel2::trade_date trade_date;
        xmt_quantumfeedlevel2::is_mid_only is_mid_only;
        xmt_quantumfeedlevel2::is_dark is_dark;
        xmt_quantumfeedlevel2::is_conditional is_conditional;
    };

    xmt_quantumfeedlevel2::business_header header = {{}, {}, {}, sequence_0(0), {}};

    fields_type fields;

    // parse method
    static trade_correction_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_correction_message*>(buffer);
    }

    // parse method const
    static const trade_correction_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_correction_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_correction_message::fields_type, symbol) == 0, "unexpected offset of trade_correction_message::fields_type::symbol");
static_assert(offsetof(trade_correction_message::fields_type, trade_number) == 12, "unexpected offset of trade_correction_message::fields_type::trade_number");
static_assert(offsetof(trade_correction_message::fields_type, price) == 16, "unexpected offset of trade_correction_message::fields_type::price");
static_assert(offsetof(trade_correction_message::fields_type, volume) == 24, "unexpected offset of trade_correction_message::fields_type::volume");
static_assert(offsetof(trade_correction_message::fields_type, buy_broker_number) == 28, "unexpected offset of trade_correction_message::fields_type::buy_broker_number");
static_assert(offsetof(trade_correction_message::fields_type, sell_broker_number) == 30, "unexpected offset of trade_correction_message::fields_type::sell_broker_number");
static_assert(offsetof(trade_correction_message::fields_type, initiated_by) == 32, "unexpected offset of trade_correction_message::fields_type::initiated_by");
static_assert(offsetof(trade_correction_message::fields_type, orig_trade_number) == 33, "unexpected offset of trade_correction_message::fields_type::orig_trade_number");
static_assert(offsetof(trade_correction_message::fields_type, bypass) == 37, "unexpected offset of trade_correction_message::fields_type::bypass");
static_assert(offsetof(trade_correction_message::fields_type, trade_time_stamp) == 38, "unexpected offset of trade_correction_message::fields_type::trade_time_stamp");
static_assert(offsetof(trade_correction_message::fields_type, cross_type) == 42, "unexpected offset of trade_correction_message::fields_type::cross_type");
static_assert(offsetof(trade_correction_message::fields_type, trading_system_time_stamp) == 43, "unexpected offset of trade_correction_message::fields_type::trading_system_time_stamp");
static_assert(offsetof(trade_correction_message::fields_type, listing_market) == 51, "unexpected offset of trade_correction_message::fields_type::listing_market");
static_assert(offsetof(trade_correction_message::fields_type, product_type) == 52, "unexpected offset of trade_correction_message::fields_type::product_type");
static_assert(offsetof(trade_correction_message::fields_type, trade_date) == 53, "unexpected offset of trade_correction_message::fields_type::trade_date");
static_assert(offsetof(trade_correction_message::fields_type, is_mid_only) == 57, "unexpected offset of trade_correction_message::fields_type::is_mid_only");
static_assert(offsetof(trade_correction_message::fields_type, is_dark) == 58, "unexpected offset of trade_correction_message::fields_type::is_dark");
static_assert(offsetof(trade_correction_message::fields_type, is_conditional) == 59, "unexpected offset of trade_correction_message::fields_type::is_conditional");
static_assert(sizeof(trade_correction_message::fields_type) == 60, "unexpected sizeof trade_correction_message::fields_type");
static_assert(sizeof(trade_correction_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 60, "unexpected sizeof trade_correction_message");

#pragma pack(pop)
}
