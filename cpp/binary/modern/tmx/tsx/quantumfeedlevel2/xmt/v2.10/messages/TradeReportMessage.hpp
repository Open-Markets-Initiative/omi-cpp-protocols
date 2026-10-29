#pragma once

#include "../types/Symbol.hpp"
#include "../types/TradeNumber.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/BuyBrokerNumber.hpp"
#include "../types/BuyOrderId.hpp"
#include "../types/BuyDisplayVolume.hpp"
#include "../types/SellBrokerNumber.hpp"
#include "../types/SellOrderId.hpp"
#include "../types/SellDisplayVolume.hpp"
#include "../types/Bypass.hpp"
#include "../types/TradeTimeStamp.hpp"
#include "../types/CrossType.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct TradeReportMessage {

    Symbol symbol;
    TradeNumber trade_number;
    Price price;
    Volume volume;
    BuyBrokerNumber buy_broker_number;
    BuyOrderId buy_order_id;
    BuyDisplayVolume buy_display_volume;
    SellBrokerNumber sell_broker_number;
    SellOrderId sell_order_id;
    SellDisplayVolume sell_display_volume;
    Bypass bypass;
    TradeTimeStamp trade_time_stamp;
    CrossType cross_type;
    TradingSystemTimeStamp trading_system_time_stamp;

    // parse method
    static TradeReportMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeReportMessage*>(buffer);
    }

    // parse method const
    static const TradeReportMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeReportMessage*>(buffer);
    }
};

#pragma pack(pop)
}
