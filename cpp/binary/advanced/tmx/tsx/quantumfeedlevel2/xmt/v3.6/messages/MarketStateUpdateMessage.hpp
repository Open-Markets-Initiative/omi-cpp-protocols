// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/MarketStateUpdateMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/BusinessHeader.hpp"
#include "../types/MarketState.hpp"
#include "../types/StockGroup.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

// Market State Update Message
struct market_state_update_message {

    struct fields_type {
        xmt_quantumfeedlevel2::market_state market_state;
        xmt_quantumfeedlevel2::stock_group stock_group;
        xmt_quantumfeedlevel2::trading_system_time_stamp trading_system_time_stamp;
    };

    xmt_quantumfeedlevel2::business_header header = {{}, {}, {}, sequence_0(0), {}};

    fields_type fields;

    // parse method
    static market_state_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<market_state_update_message*>(buffer);
    }

    // parse method const
    static const market_state_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const market_state_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(market_state_update_message::fields_type, market_state) == 0, "unexpected offset of market_state_update_message::fields_type::market_state");
static_assert(offsetof(market_state_update_message::fields_type, stock_group) == 1, "unexpected offset of market_state_update_message::fields_type::stock_group");
static_assert(offsetof(market_state_update_message::fields_type, trading_system_time_stamp) == 2, "unexpected offset of market_state_update_message::fields_type::trading_system_time_stamp");
static_assert(sizeof(market_state_update_message::fields_type) == 10, "unexpected sizeof market_state_update_message::fields_type");
static_assert(sizeof(market_state_update_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 10, "unexpected sizeof market_state_update_message");

#pragma pack(pop)
}
