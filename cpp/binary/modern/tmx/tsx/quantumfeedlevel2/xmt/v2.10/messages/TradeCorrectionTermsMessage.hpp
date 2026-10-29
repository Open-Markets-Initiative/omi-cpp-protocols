#pragma once

#include "../types/Symbol.hpp"
#include "../types/TradeNumber.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/BuyBrokerNumber.hpp"
#include "../types/SellBrokerNumber.hpp"
#include "../types/InitiatedBy.hpp"
#include "../types/OrigTradeNumber.hpp"
#include "../types/TradeTimeStamp.hpp"
#include "../types/NonResident.hpp"
#include "../types/SettlementTerms.hpp"
#include "../types/SettlementDate.hpp"
#include "../types/CrossType.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct TradeCorrectionTermsMessage {

    Symbol symbol;
    TradeNumber trade_number;
    Price price;
    Volume volume;
    BuyBrokerNumber buy_broker_number;
    SellBrokerNumber sell_broker_number;
    InitiatedBy initiated_by;
    OrigTradeNumber orig_trade_number;
    TradeTimeStamp trade_time_stamp;
    NonResident non_resident;
    SettlementTerms settlement_terms;
    SettlementDate settlement_date;
    CrossType cross_type;
    TradingSystemTimeStamp trading_system_time_stamp;

    // parse method
    static TradeCorrectionTermsMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCorrectionTermsMessage*>(buffer);
    }

    // parse method const
    static const TradeCorrectionTermsMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCorrectionTermsMessage*>(buffer);
    }
};

#pragma pack(pop)
}
