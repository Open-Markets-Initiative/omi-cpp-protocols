// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/TradeReportTermsMessage.hpp
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
#include "../types/TradeTimeStamp.hpp"
#include "../types/NonResident.hpp"
#include "../types/SettlementTerms.hpp"
#include "../types/SettlementDate.hpp"
#include "../types/CrossType.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

// Trade Report Terms Message
struct trade_report_terms_message {

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
        xmt_quantumfeedlevel2::trade_time_stamp trade_time_stamp;
        xmt_quantumfeedlevel2::non_resident non_resident;
        xmt_quantumfeedlevel2::settlement_terms settlement_terms;
        xmt_quantumfeedlevel2::settlement_date settlement_date;
        xmt_quantumfeedlevel2::cross_type cross_type;
        xmt_quantumfeedlevel2::trading_system_time_stamp trading_system_time_stamp;
    };

    xmt_quantumfeedlevel2::business_header header = {{}, {}, {}, sequence_0(0), {}};

    fields_type fields;

    // parse method
    static trade_report_terms_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_report_terms_message*>(buffer);
    }

    // parse method const
    static const trade_report_terms_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_report_terms_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_report_terms_message::fields_type, symbol) == 0, "unexpected offset of trade_report_terms_message::fields_type::symbol");
static_assert(offsetof(trade_report_terms_message::fields_type, trade_number) == 12, "unexpected offset of trade_report_terms_message::fields_type::trade_number");
static_assert(offsetof(trade_report_terms_message::fields_type, price) == 16, "unexpected offset of trade_report_terms_message::fields_type::price");
static_assert(offsetof(trade_report_terms_message::fields_type, volume) == 24, "unexpected offset of trade_report_terms_message::fields_type::volume");
static_assert(offsetof(trade_report_terms_message::fields_type, buy_broker_number) == 28, "unexpected offset of trade_report_terms_message::fields_type::buy_broker_number");
static_assert(offsetof(trade_report_terms_message::fields_type, buy_order_id) == 30, "unexpected offset of trade_report_terms_message::fields_type::buy_order_id");
static_assert(offsetof(trade_report_terms_message::fields_type, buy_display_volume) == 38, "unexpected offset of trade_report_terms_message::fields_type::buy_display_volume");
static_assert(offsetof(trade_report_terms_message::fields_type, sell_broker_number) == 42, "unexpected offset of trade_report_terms_message::fields_type::sell_broker_number");
static_assert(offsetof(trade_report_terms_message::fields_type, sell_order_id) == 44, "unexpected offset of trade_report_terms_message::fields_type::sell_order_id");
static_assert(offsetof(trade_report_terms_message::fields_type, sell_display_volume) == 52, "unexpected offset of trade_report_terms_message::fields_type::sell_display_volume");
static_assert(offsetof(trade_report_terms_message::fields_type, trade_time_stamp) == 56, "unexpected offset of trade_report_terms_message::fields_type::trade_time_stamp");
static_assert(offsetof(trade_report_terms_message::fields_type, non_resident) == 60, "unexpected offset of trade_report_terms_message::fields_type::non_resident");
static_assert(offsetof(trade_report_terms_message::fields_type, settlement_terms) == 61, "unexpected offset of trade_report_terms_message::fields_type::settlement_terms");
static_assert(offsetof(trade_report_terms_message::fields_type, settlement_date) == 62, "unexpected offset of trade_report_terms_message::fields_type::settlement_date");
static_assert(offsetof(trade_report_terms_message::fields_type, cross_type) == 66, "unexpected offset of trade_report_terms_message::fields_type::cross_type");
static_assert(offsetof(trade_report_terms_message::fields_type, trading_system_time_stamp) == 67, "unexpected offset of trade_report_terms_message::fields_type::trading_system_time_stamp");
static_assert(sizeof(trade_report_terms_message::fields_type) == 75, "unexpected sizeof trade_report_terms_message::fields_type");
static_assert(sizeof(trade_report_terms_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 75, "unexpected sizeof trade_report_terms_message");

#pragma pack(pop)
}
