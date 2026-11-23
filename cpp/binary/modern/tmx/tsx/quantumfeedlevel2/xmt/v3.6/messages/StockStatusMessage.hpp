// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/StockStatusMessage.hpp
#pragma once

#include "../types/Symbol.hpp"
#include "../types/Comment.hpp"
#include "../types/StockState.hpp"
#include "../types/TradingSystemTimeStamp.hpp"
#include "../types/ListingMarket.hpp"
#include "../types/ProductType.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

#pragma pack(push, 1)

// 
struct StockStatusMessage {

    Symbol symbol;
    Comment comment;
    StockState stock_state;
    TradingSystemTimeStamp trading_system_time_stamp;
    ListingMarket listing_market;
    ProductType product_type;

    // parse method
    static StockStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StockStatusMessage*>(buffer);
    }

    // parse method const
    static const StockStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StockStatusMessage*>(buffer);
    }
};

#pragma pack(pop)
}
