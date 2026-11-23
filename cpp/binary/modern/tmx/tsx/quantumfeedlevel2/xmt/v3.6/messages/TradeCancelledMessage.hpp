// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/TradeCancelledMessage.hpp
#pragma once

#include "../types/Symbol.hpp"
#include "../types/TradeNumber.hpp"
#include "../types/TradingSystemTimeStamp.hpp"
#include "../types/ListingMarket.hpp"
#include "../types/ProductType.hpp"
#include "../types/TradeDate.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

#pragma pack(push, 1)

// 
struct TradeCancelledMessage {

    Symbol symbol;
    TradeNumber trade_number;
    TradingSystemTimeStamp trading_system_time_stamp;
    ListingMarket listing_market;
    ProductType product_type;
    TradeDate trade_date;

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
