#pragma once

#include "../types/Symbol.hpp"
#include "../types/BrokerNumber.hpp"
#include "../types/OrderSide.hpp"
#include "../types/OrderId.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct OrderCancelledTermsMessage {

    Symbol symbol;
    BrokerNumber broker_number;
    OrderSide order_side;
    OrderId order_id;
    TradingSystemTimeStamp trading_system_time_stamp;

    // parse method
    static OrderCancelledTermsMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderCancelledTermsMessage*>(buffer);
    }

    // parse method const
    static const OrderCancelledTermsMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderCancelledTermsMessage*>(buffer);
    }
};

#pragma pack(pop)
}
