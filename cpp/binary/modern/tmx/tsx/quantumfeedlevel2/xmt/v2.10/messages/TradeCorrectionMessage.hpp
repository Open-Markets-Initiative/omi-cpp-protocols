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

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

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
