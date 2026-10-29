#pragma once

#include "../types/Symbol.hpp"
#include "../types/BrokerNumber.hpp"
#include "../types/OrderSide.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PriorityTimeStamp.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct OrderBookedMessage {

    Symbol symbol;
    BrokerNumber broker_number;
    OrderSide order_side;
    OrderId order_id;
    Price price;
    Volume volume;
    PriorityTimeStamp priority_time_stamp;
    TradingSystemTimeStamp trading_system_time_stamp;

    // parse method
    static OrderBookedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderBookedMessage*>(buffer);
    }

    // parse method const
    static const OrderBookedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderBookedMessage*>(buffer);
    }
};

#pragma pack(pop)
}
