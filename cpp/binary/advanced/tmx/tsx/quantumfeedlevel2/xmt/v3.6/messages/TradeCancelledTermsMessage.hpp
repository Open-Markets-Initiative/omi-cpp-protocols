// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/TradeCancelledTermsMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/BusinessHeader.hpp"
#include "../types/Symbol.hpp"
#include "../types/TradeNumber.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

// Trade Cancelled Terms Message
struct trade_cancelled_terms_message {

    struct fields_type {
        xmt_quantumfeedlevel2::symbol symbol;
        xmt_quantumfeedlevel2::trade_number trade_number;
        xmt_quantumfeedlevel2::trading_system_time_stamp trading_system_time_stamp;
    };

    xmt_quantumfeedlevel2::business_header header = {{}, {}, {}, sequence_0(0), {}};

    fields_type fields;

    // parse method
    static trade_cancelled_terms_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_cancelled_terms_message*>(buffer);
    }

    // parse method const
    static const trade_cancelled_terms_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_cancelled_terms_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_cancelled_terms_message::fields_type, symbol) == 0, "unexpected offset of trade_cancelled_terms_message::fields_type::symbol");
static_assert(offsetof(trade_cancelled_terms_message::fields_type, trade_number) == 12, "unexpected offset of trade_cancelled_terms_message::fields_type::trade_number");
static_assert(offsetof(trade_cancelled_terms_message::fields_type, trading_system_time_stamp) == 16, "unexpected offset of trade_cancelled_terms_message::fields_type::trading_system_time_stamp");
static_assert(sizeof(trade_cancelled_terms_message::fields_type) == 24, "unexpected sizeof trade_cancelled_terms_message::fields_type");
static_assert(sizeof(trade_cancelled_terms_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 24, "unexpected sizeof trade_cancelled_terms_message");

#pragma pack(pop)
}
