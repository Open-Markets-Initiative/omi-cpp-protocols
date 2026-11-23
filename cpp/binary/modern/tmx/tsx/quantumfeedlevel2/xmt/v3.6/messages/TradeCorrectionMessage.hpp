// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/TradeCorrectionMessage.hpp
#pragma once

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
#include "../types/ListingMarket.hpp"
#include "../types/ProductType.hpp"
#include "../types/TradeDate.hpp"
#include "../types/IsMidOnly.hpp"
#include "../types/IsDark.hpp"
#include "../types/IsConditional.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

#pragma pack(push, 1)

// 
struct TradeCorrectionMessage {

    Symbol symbol;
    TradeNumber trade_number;
    Price price;
    Volume volume;
    BuyBrokerNumber buy_broker_number;
    SellBrokerNumber sell_broker_number;
    InitiatedBy initiated_by;
    OrigTradeNumber orig_trade_number;
    Bypass bypass;
    TradeTimeStamp trade_time_stamp;
    CrossType cross_type;
    TradingSystemTimeStamp trading_system_time_stamp;
    ListingMarket listing_market;
    ProductType product_type;
    TradeDate trade_date;
    IsMidOnly is_mid_only;
    IsDark is_dark;
    IsConditional is_conditional;

    // parse method
    static TradeCorrectionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCorrectionMessage*>(buffer);
    }

    // parse method const
    static const TradeCorrectionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCorrectionMessage*>(buffer);
    }
};

#pragma pack(pop)
}
