// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/TradeCorrectionMessage.hpp
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

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v2_10;

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
static_assert(offsetof(trade_correction_message::fields_type, trade_number) == 9, "unexpected offset of trade_correction_message::fields_type::trade_number");
static_assert(offsetof(trade_correction_message::fields_type, price) == 13, "unexpected offset of trade_correction_message::fields_type::price");
static_assert(offsetof(trade_correction_message::fields_type, volume) == 21, "unexpected offset of trade_correction_message::fields_type::volume");
static_assert(offsetof(trade_correction_message::fields_type, buy_broker_number) == 25, "unexpected offset of trade_correction_message::fields_type::buy_broker_number");
static_assert(offsetof(trade_correction_message::fields_type, sell_broker_number) == 27, "unexpected offset of trade_correction_message::fields_type::sell_broker_number");
static_assert(offsetof(trade_correction_message::fields_type, initiated_by) == 29, "unexpected offset of trade_correction_message::fields_type::initiated_by");
static_assert(offsetof(trade_correction_message::fields_type, orig_trade_number) == 30, "unexpected offset of trade_correction_message::fields_type::orig_trade_number");
static_assert(offsetof(trade_correction_message::fields_type, bypass) == 34, "unexpected offset of trade_correction_message::fields_type::bypass");
static_assert(offsetof(trade_correction_message::fields_type, trade_time_stamp) == 35, "unexpected offset of trade_correction_message::fields_type::trade_time_stamp");
static_assert(offsetof(trade_correction_message::fields_type, cross_type) == 39, "unexpected offset of trade_correction_message::fields_type::cross_type");
static_assert(offsetof(trade_correction_message::fields_type, trading_system_time_stamp) == 40, "unexpected offset of trade_correction_message::fields_type::trading_system_time_stamp");
static_assert(sizeof(trade_correction_message::fields_type) == 48, "unexpected sizeof trade_correction_message::fields_type");
static_assert(sizeof(trade_correction_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 48, "unexpected sizeof trade_correction_message");

#pragma pack(pop)
}
