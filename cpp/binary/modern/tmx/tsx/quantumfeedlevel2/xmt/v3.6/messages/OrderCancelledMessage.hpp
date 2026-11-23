// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/OrderCancelledMessage.hpp
#pragma once

#include "../types/Symbol.hpp"
#include "../types/BrokerNumber.hpp"
#include "../types/OrderSide.hpp"
#include "../types/OrderId.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

#pragma pack(push, 1)

// 
struct OrderCancelledMessage {

    Symbol symbol;
    BrokerNumber broker_number;
    OrderSide order_side;
    OrderId order_id;
    TradingSystemTimeStamp trading_system_time_stamp;

    // parse method
    static OrderCancelledMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderCancelledMessage*>(buffer);
    }

    // parse method const
    static const OrderCancelledMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderCancelledMessage*>(buffer);
    }
};

#pragma pack(pop)
}
