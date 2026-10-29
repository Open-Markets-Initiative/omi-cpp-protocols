#pragma once

#include "../types/Symbol.hpp"
#include "../types/TradeNumber.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct TradeCancelledTermsMessage {

    Symbol symbol;
    TradeNumber trade_number;
    TradingSystemTimeStamp trading_system_time_stamp;

    // parse method
    static TradeCancelledTermsMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCancelledTermsMessage*>(buffer);
    }

    // parse method const
    static const TradeCancelledTermsMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCancelledTermsMessage*>(buffer);
    }
};

#pragma pack(pop)
}
