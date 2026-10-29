#pragma once

#include "../types/Symbol.hpp"
#include "../types/TradeNumber.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct TradeCancelledMessage {

    Symbol symbol;
    TradeNumber trade_number;
    TradingSystemTimeStamp trading_system_time_stamp;

    // parse method
    static TradeCancelledMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCancelledMessage*>(buffer);
    }

    // parse method const
    static const TradeCancelledMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCancelledMessage*>(buffer);
    }
};

#pragma pack(pop)
}
