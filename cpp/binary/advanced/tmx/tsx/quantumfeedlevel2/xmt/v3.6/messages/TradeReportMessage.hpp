// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/TradeReportMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/BusinessHeader.hpp"
#include "../types/Symbol.hpp"
#include "../types/TradeNumber.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/BuyBrokerNumber.hpp"
#include "../types/BuyOrderId.hpp"
#include "../types/BuyDisplayVolume.hpp"
#include "../types/SellBrokerNumber.hpp"
#include "../types/SellOrderId.hpp"
#include "../types/SellDisplayVolume.hpp"
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

// Trade Report Message
struct trade_report_message {

    struct fields_type {
        xmt_quantumfeedlevel2::symbol symbol;
        xmt_quantumfeedlevel2::trade_number trade_number;
        xmt_quantumfeedlevel2::price price;
        xmt_quantumfeedlevel2::volume volume;
        xmt_quantumfeedlevel2::buy_broker_number buy_broker_number;
        xmt_quantumfeedlevel2::buy_order_id buy_order_id;
        xmt_quantumfeedlevel2::buy_display_volume buy_display_volume;
        xmt_quantumfeedlevel2::sell_broker_number sell_broker_number;
        xmt_quantumfeedlevel2::sell_order_id sell_order_id;
        xmt_quantumfeedlevel2::sell_display_volume sell_display_volume;
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
    static trade_report_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_report_message*>(buffer);
    }

    // parse method const
    static const trade_report_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_report_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_report_message::fields_type, symbol) == 0, "unexpected offset of trade_report_message::fields_type::symbol");
static_assert(offsetof(trade_report_message::fields_type, trade_number) == 12, "unexpected offset of trade_report_message::fields_type::trade_number");
static_assert(offsetof(trade_report_message::fields_type, price) == 16, "unexpected offset of trade_report_message::fields_type::price");
static_assert(offsetof(trade_report_message::fields_type, volume) == 24, "unexpected offset of trade_report_message::fields_type::volume");
static_assert(offsetof(trade_report_message::fields_type, buy_broker_number) == 28, "unexpected offset of trade_report_message::fields_type::buy_broker_number");
static_assert(offsetof(trade_report_message::fields_type, buy_order_id) == 30, "unexpected offset of trade_report_message::fields_type::buy_order_id");
static_assert(offsetof(trade_report_message::fields_type, buy_display_volume) == 38, "unexpected offset of trade_report_message::fields_type::buy_display_volume");
static_assert(offsetof(trade_report_message::fields_type, sell_broker_number) == 42, "unexpected offset of trade_report_message::fields_type::sell_broker_number");
static_assert(offsetof(trade_report_message::fields_type, sell_order_id) == 44, "unexpected offset of trade_report_message::fields_type::sell_order_id");
static_assert(offsetof(trade_report_message::fields_type, sell_display_volume) == 52, "unexpected offset of trade_report_message::fields_type::sell_display_volume");
static_assert(offsetof(trade_report_message::fields_type, bypass) == 56, "unexpected offset of trade_report_message::fields_type::bypass");
static_assert(offsetof(trade_report_message::fields_type, trade_time_stamp) == 57, "unexpected offset of trade_report_message::fields_type::trade_time_stamp");
static_assert(offsetof(trade_report_message::fields_type, cross_type) == 61, "unexpected offset of trade_report_message::fields_type::cross_type");
static_assert(offsetof(trade_report_message::fields_type, trading_system_time_stamp) == 62, "unexpected offset of trade_report_message::fields_type::trading_system_time_stamp");
static_assert(offsetof(trade_report_message::fields_type, listing_market) == 70, "unexpected offset of trade_report_message::fields_type::listing_market");
static_assert(offsetof(trade_report_message::fields_type, product_type) == 71, "unexpected offset of trade_report_message::fields_type::product_type");
static_assert(offsetof(trade_report_message::fields_type, trade_date) == 72, "unexpected offset of trade_report_message::fields_type::trade_date");
static_assert(offsetof(trade_report_message::fields_type, is_mid_only) == 76, "unexpected offset of trade_report_message::fields_type::is_mid_only");
static_assert(offsetof(trade_report_message::fields_type, is_dark) == 77, "unexpected offset of trade_report_message::fields_type::is_dark");
static_assert(offsetof(trade_report_message::fields_type, is_conditional) == 78, "unexpected offset of trade_report_message::fields_type::is_conditional");
static_assert(sizeof(trade_report_message::fields_type) == 79, "unexpected sizeof trade_report_message::fields_type");
static_assert(sizeof(trade_report_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 79, "unexpected sizeof trade_report_message");

#pragma pack(pop)
}
