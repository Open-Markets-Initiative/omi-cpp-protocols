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
#include "../types/TradeTimeStamp.hpp"
#include "../types/NonResident.hpp"
#include "../types/SettlementTerms.hpp"
#include "../types/SettlementDate.hpp"
#include "../types/CrossType.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct TradeReportTermsMessage {

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
    TradeTimeStamp trade_time_stamp;
    NonResident non_resident;
    SettlementTerms settlement_terms;
    SettlementDate settlement_date;
    CrossType cross_type;
    TradingSystemTimeStamp trading_system_time_stamp;

    // parse method
    static TradeReportTermsMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeReportTermsMessage*>(buffer);
    }

    // parse method const
    static const TradeReportTermsMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeReportTermsMessage*>(buffer);
    }
};

#pragma pack(pop)
}
