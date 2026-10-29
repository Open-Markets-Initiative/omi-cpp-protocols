#pragma once

#include "../types/MarketState.hpp"
#include "../types/StockGroup.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct MarketStateUpdateMessage {

    MarketState market_state;
    StockGroup stock_group;
    TradingSystemTimeStamp trading_system_time_stamp;

    // parse method
    static MarketStateUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MarketStateUpdateMessage*>(buffer);
    }

    // parse method const
    static const MarketStateUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketStateUpdateMessage*>(buffer);
    }
};

#pragma pack(pop)
}
